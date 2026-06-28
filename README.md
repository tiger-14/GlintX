# GlintX
GlintX is a sleek, hands-free phone cleaning station that automatically removes fingerprints, dust, and surface grime with a single button press. 

<img width="605" height="519" alt="image" src="https://github.com/user-attachments/assets/a4032953-fee0-4741-81ac-01d403dace7a" />

*(this is a finsihed render model of our product with a transparent wall, will update once we assemble the full thing physically!)*

## Live demo video
https://youtu.be/upcu00X-KWE

*This is just a demo of the 3D model, will update once we assemble the full thing physically*

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
The user places their phone inside the station and presses the start button. Actuated by the Arduino, two high-torque TT metal gearmotors rotate a pair of threaded rods. The TT motors were chosen over other motors due to their low cosdt and low RPM with high torque. This rotational force drives the 3D-printed carriage smoothly along the length of the screen. As the carriage travels, the microfiber roller cleans the front and back of the phone while a peristaltic pump pushes cleaning fluid through the pipe and then through the 0.1mm brass misting high pressure nozzles. Concurrently, a vibration disc dislodges stubborn debris near the ports and speakers of the phone, and UV lights sanitize the surface. Once the carriage hits the mechanical endstop limit switch, the Arduino reverses the TT motors, spinning the threaded rods backward to reverse the carriage's direction. Limit switches were used so that we could use cost-effective DC motors (these motors cannot count their own rotations).

## Bill of Materials
## Bill of Materials

| Part | Link | Price |
|------|------|-------|
| Arduino Uno Rev3 | [Link](https://www.microcenter.com/product/618839) | $27.99 |
| 4 Channel Motor Shield | [Link](https://www.microcenter.com/product/639730/inland-ks0448-keyestudio-l298p-4-channel-motor-drive-shield) | $30.00 |
| 2x TT Motors with Encoder | [Link](https://www.amazon.com/TT-Encoder-Motor-All-Metal-Robotics/dp/B0GHYFZ2SQ) | $26.99 |
| R360 Small Electric Motor | [Link](https://www.microcenter.com/product/497116/leo-sales-ltd-r360-small-electric-motor) | $5.99 |
| Jumper Wires | [Link](https://www.microcenter.com/product/613879/inland-dupont-jumper-wire-20cm-3-pack) | $4.99 |
| Alligator Wires | [Link](https://www.amazon.com/Dupont-Breadboard-Jumper-Alligator-Arduino/dp/B07NWLW6P9) | $8.99 |
| UV LED Strip | [Link](https://www.amazon.com/Strips-Flexible-Blacklight-Non-Waterproof-Halloween/dp/B0B8Z7P38X) | $7.99 |
| Limit Switches | [Link](https://www.amazon.com/ALMOCN-Mechanical-Endstop-Switch-Printer/dp/B08L5W4WM5) | $8.99 |
| 12V Power Supply | [Link](https://www.amazon.com/GuanTing-Universal-adapters-Converter-Transformer/dp/B086T1N5R4) | $8.28 |
| Lead Screws | [Link](https://www.amazon.com/200mm%EF%BC%887-88-Inches%EF%BC%89-Thread-Printer-Machine/dp/B0BWYLKVYN) | $11.99 |
| Peristaltic Pump | [Link](https://www.amazon.com/Kamoer-Peristaltic-Hydroponics-Nutrient-Analytical/dp/B07GWJ78FN) | $8.48 |
| Microfiber Roller | [Link](https://www.amazon.com/Mister-Rui-Microfiber-Painting-Cabinets/dp/B0DXPQPMH1) | $6.40 |
| Silicone Tubing | [Link](https://www.amazon.com/Quickun-Silicone-Brewing-Kegerator-Aquaponics/dp/B08BRC5FPB) | $5.99 |
| Illuminated Push Button | [Link](https://www.amazon.com/Starelo-Momentary-Button-Waterproof-Self-resetting/dp/B0BVPSFJCY) | $11.19 |
| Rod Coupler | [Link](https://www.amazon.com/dp/B0FN7BC55F) | $7.79 |
| Cable Adapters | [Link](https://www.amazon.com/Connector-Connectors-Female-Silicone-Cables/dp/B0GWYR7CQ2) | $5.99 |
| Vibrating Disc Motor | [Link](https://www.microcenter.com/product/454448/adafruit-industries-vibrating-mini-motor-disc) | $1.99 |
| M3 Screw Kit | [Link](https://www.amazon.com/Fgruh-750PCS-Assortment-Washers-Assorted/dp/B0FGV5FCBN) | $9.99 |
| Magnetic Tape | [Link](https://www.amazon.com/Magnetic-Flexible-Adhesive-Backing-Magnets/dp/B0D82YQM2B) | $8.99 |
| Misting Nozzles | [Link](https://www.amazon.com/Virello-Threaded-Pressure-Greenhouse-Landscaping/dp/B0GD74KXPL) | $7.79 |
| **Total** | | **$216.80** |

## Credits
Built in collaboration with Benjamin Antony ([@Benfa-1](https://github.com/Benfa-1)) for Hack Club's Stardance 2026. 

AI Usage
-Used AI to check whether the parts selected would work as intended for our project.
-Used AI to find part dimensions of parts without listed dimensions hwo do i put this in ai usage decalration

## License
<img width="210" height="109" alt="image" src="https://github.com/user-attachments/assets/47ddd400-2bfc-4b73-9769-2a699ef808d7" />
