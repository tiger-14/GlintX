// ================================
// GlintX - Phone Cleaning Station
// Arduino Uno + L298P 4-Channel Motor Shield V1.0
// Synchronized with Encoders (EnableInterrupt Library Required)
// ================================

#include <EnableInterrupt.h>

// --- MOTOR SHIELD PINS ---
#define MOT_A_EN  6
#define MOT_A_DIR 3
#define MOT_B_EN  5
#define MOT_B_DIR 4
#define MOT_C_EN  10
#define MOT_C_DIR 7
#define MOT_D_EN  9
#define MOT_D_DIR 8

// --- OTHER PINS ---
#define BUTTON_PIN      2
#define BUTTON_LED      13
#define LIMIT_BOTTOM_A 11
#define LIMIT_BOTTOM_B 12
#define DISC_PIN       A0
#define UV_PIN         A1

// --- ENCODER PINS ---
#define ENC_A_PHASE_A  A2
#define ENC_A_PHASE_B  A4
#define ENC_B_PHASE_A  A3
#define ENC_B_PHASE_B  A5

// --- TUNABLE SETTINGS ---
#define BASE_SPEED_DOWN      180
#define BASE_SPEED_UP        230
#define ROLLER_SPEED         200
#define PUMP_DURATION        800
#define PUMP_INTERVAL        1000  // spray repeatedly within the window
#define TOTAL_CYCLE_TIME     40000
#define SPRAY_WINDOW         5000  // only spray in first 5 seconds
#define UP_TIME              8500

// --- GLOBAL ENCODER VARIABLES ---
volatile long encoderCountA = 0;
volatile long encoderCountB = 0;

void isrEncoderA() {
  if (digitalRead(ENC_A_PHASE_A) == digitalRead(ENC_A_PHASE_B)) {
    encoderCountA++;
  } else {
    encoderCountA--;
  }
}

void isrEncoderB() {
  if (digitalRead(ENC_B_PHASE_A) == digitalRead(ENC_B_PHASE_B)) {
    encoderCountB++;
  } else {
    encoderCountB--;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(MOT_A_EN,  OUTPUT);
  pinMode(MOT_A_DIR, OUTPUT);
  pinMode(MOT_B_EN,  OUTPUT);
  pinMode(MOT_B_DIR, OUTPUT);
  pinMode(MOT_C_EN,  OUTPUT);
  pinMode(MOT_C_DIR, OUTPUT);
  pinMode(MOT_D_EN,  OUTPUT);
  pinMode(MOT_D_DIR, OUTPUT);

  pinMode(BUTTON_PIN,     INPUT_PULLUP);
  pinMode(BUTTON_LED,     OUTPUT);
  pinMode(LIMIT_BOTTOM_A, INPUT_PULLUP);
  pinMode(LIMIT_BOTTOM_B, INPUT_PULLUP);
  pinMode(DISC_PIN,       OUTPUT);
  pinMode(UV_PIN,         OUTPUT);

  pinMode(ENC_A_PHASE_A, INPUT_PULLUP);
  pinMode(ENC_A_PHASE_B, INPUT_PULLUP);
  pinMode(ENC_B_PHASE_A, INPUT_PULLUP);
  pinMode(ENC_B_PHASE_B, INPUT_PULLUP);

  enableInterrupt(ENC_A_PHASE_A, isrEncoderA, CHANGE);
  enableInterrupt(ENC_B_PHASE_A, isrEncoderB, CHANGE);

  stopAll();

  for (int i = 0; i < 3; i++) {
    digitalWrite(BUTTON_LED, HIGH);
    delay(200);
    digitalWrite(BUTTON_LED, LOW);
    delay(200);
  }

  Serial.println("GlintX ready. Press button to start.");
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(50);
    if (digitalRead(BUTTON_PIN) == LOW) {
      runCleaningCycle();
    }
  }
}

bool bottomReached() {
  return (digitalRead(LIMIT_BOTTOM_A) == LOW || digitalRead(LIMIT_BOTTOM_B) == LOW);
}

void driveCarriageSync(bool goingDown, int baseSpeed) {
  if (goingDown) {
    digitalWrite(MOT_A_DIR, HIGH);
    digitalWrite(MOT_B_DIR, HIGH);
  } else {
    digitalWrite(MOT_A_DIR, LOW);
    digitalWrite(MOT_B_DIR, LOW);
  }

  long diff = abs(encoderCountA) - abs(encoderCountB);
  int kP = 2;

  int speedA = baseSpeed - (diff * kP);
  int speedB = baseSpeed + (diff * kP);

  speedA = constrain(speedA, 100, 255);
  speedB = constrain(speedB, 100, 255);

  analogWrite(MOT_A_EN, speedA);
  analogWrite(MOT_B_EN, speedB);
}

void runCleaningCycle() {
  Serial.println("=== Cycle started ===");
  digitalWrite(BUTTON_LED, HIGH);
  digitalWrite(UV_PIN, HIGH);
  digitalWrite(DISC_PIN, HIGH);
  startRoller();

  encoderCountA = 0;
  encoderCountB = 0;

  unsigned long cycleStart     = millis();
  unsigned long lastSpray      = millis();
  bool goingDown               = true;
  unsigned long directionStart = millis();
  bool printedDrying           = false;

  while (millis() - cycleStart < TOTAL_CYCLE_TIME) {

    int currentBaseSpeed = goingDown ? BASE_SPEED_DOWN : BASE_SPEED_UP;
    driveCarriageSync(goingDown, currentBaseSpeed);

    // Only spray in first SPRAY_WINDOW ms
    bool inSprayWindow = (millis() - cycleStart < SPRAY_WINDOW);
    if (inSprayWindow) {
      if (millis() - lastSpray >= PUMP_INTERVAL) {
        sprayFluid();
        lastSpray = millis();
      }
    } else if (!printedDrying) {
      Serial.println(">>> Drying phase. Pump disabled. <<<");
      printedDrying = true;
    }

    if (goingDown) {
      if (bottomReached()) {
        Serial.println("Limit hit. Reversing up instantly.");
        goingDown = false;
        directionStart = millis();
        encoderCountA = 0;
        encoderCountB = 0;
      }
    } else {
      if (millis() - directionStart >= UP_TIME) {
        Serial.println("Top reached. Reversing down.");
        goingDown = true;
        directionStart = millis();
        encoderCountA = 0;
        encoderCountB = 0;
      }
    }
  }

  Serial.println("Cycle complete. Centering carriage...");
  stopCarriage();
  encoderCountA = 0;
  encoderCountB = 0;

  while (!bottomReached()) {
    driveCarriageSync(true, BASE_SPEED_DOWN);
  }

  stopCarriage();
  encoderCountA = 0;
  encoderCountB = 0;

  unsigned long centerStart = millis();
  while (millis() - centerStart < (UP_TIME / 2)) {
    driveCarriageSync(false, BASE_SPEED_UP);
  }

  stopCarriage();

  Serial.println("=== Done. Carriage centered. ===");
  stopAll();
  delay(500);
  digitalWrite(BUTTON_LED, LOW);
}

void stopCarriage() {
  analogWrite(MOT_A_EN, 0);
  analogWrite(MOT_B_EN, 0);
}

void startRoller() {
  digitalWrite(MOT_C_DIR, HIGH);
  analogWrite(MOT_C_EN, ROLLER_SPEED);
}

void sprayFluid() {
  Serial.prin\]ytln("Spraying...");
  digitalWrite(MOT_D_DIR, HIGH);
  analogWrite(MOT_D_EN, 255);
  delay(PUMP_DURATION);
  analogWrite(MOT_D_EN, 0);
}

void stopAll() {
  analogWrite(MOT_A_EN, 0);
  analogWrite(MOT_B_EN, 0);
  analogWrite(MOT_C_EN, 0);
  analogWrite(MOT_D_EN, 0);
  digitalWrite(DISC_PIN, LOW);
  digitalWrite(UV_PIN,   LOW);
}

void errorBlink() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(BUTTON_LED, HIGH);
    delay(100);
    digitalWrite(BUTTON_LED, LOW);
    delay(100);
  }
}
