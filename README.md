# GlintX

GlintX is a sleek, hands-free phone cleaning station that automatically removes fingerprints, dust, and surface grime with a single button press. 

(insert image)

## Features
- 3D-printed carriage driven by a combination of high-torque TT metal gearmotors and threaded rods
- Spinning microfiber roller for physical screen cleaning
- 4x high-pressure brass misting nozzles (0.1mm orifice) 
- Peristaltic pump fluid delivery system
- UV sanitization light
- Vibration disc  for debris dislodging 
- Arduino-controlled
- Mechanical endstop limit switches for automatic carriage reversal
- Fully 3D printed enclosure and carriage

## How it works
The user places their phone inside the station and presses the start button. Actuated by the Arduino, two high-torque TT metal gearmotors rotate a pair of threaded rods. The TT motors were chosen over other motors due to their low cosdt and low RPM with high torque. This rotational force drives the 3D-printed carriage smoothly along the length of the screen. As the carriage travels, a secondary motor spins the microfiber roller for physical scrubbing while a peristaltic pump pushes cleaning fluid through the 0.1mm brass misting nozzles. Concurrently, a vibration disc dislodges stubborn debris near the ports and speakers of the phone, and UV lights sanitize the surface. Once the carriage hits the mechanical endstop limit switch, the Arduino reverses the TT motors, spinning the threaded rods backward to reverse the carriage's direction. Limit switches were used so that we could use cost-effective DC motors (these motors cannot count their own rotations).
