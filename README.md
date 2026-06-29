# YieldGuard

## An automatic Milk Weight Logging System using ESP32, HX711 and Load Cell

### How it works:
1. The whole hardware sits under the milk collection Jar.
2. The milk gets collected inside the Jar - Hardware silently notices it.
3. When the milking completes, the weight becomes stable.
4. Once it stabilizes for more than 3 minutes, the milk weight gets logged and is sent over WhatsApp as a message.
5. It repeats :)

#### How to use it?

1. Go over to [JLCPCB](https://jlcpcb.com/).
2. Download the Gerber Files from this repository and upload them there and order PCB.
3. Use the links in BoM (Bill of Materials) to order other components (The 3D Case can either be 3D-Printed or pre-made case can be ordered).
4. Solder all the components on PCB and wire them properly as per the Schematic Diagram.
5. Connect ESP32 with your device and boot the Calibration Code in it.
6. Follow all the instructions mentioned in Serial Monitor to calibrate the Load Cell Specs etc.
7. Boot ESP32 with the main code given in Firmware/Main/main.ino file.
8. That's all :) Enjoy.

#### Why I built this?

I built this project to solve the real problem we faced at our farm - manual milk logging was quite difficult and unreliable. This automatic milk logging system makes the system highly reliable and efficient.

#### Screenshots:

<img width="730" height="576" alt="PCB Design (2)" src="https://github.com/user-attachments/assets/aae91988-b8ab-44af-a0be-d24838c0f379" />
<img width="720" height="566" alt="PCB Design (1)" src="https://github.com/user-attachments/assets/6f3d2518-711e-4a42-ae3f-47c35e51b611" />
<img width="717" height="567" alt="Assembled Image 2" src="https://github.com/user-attachments/assets/08dc56a1-d4a3-49c9-af65-d6e10dc88c08" />
<img width="777" height="553" alt="Assembled Image 1" src="https://github.com/user-attachments/assets/301a611a-7cc2-4d3e-8544-50fcdbbc3b37" />
<img width="573" height="424" alt="3D Image PCB" src="https://github.com/user-attachments/assets/58cf9de8-4d0c-4106-823e-6059a5be19d6" />


#### Bill of Materials

| Item Name | Quantity | Link | Cost |
| :--- | :---: | :--- | :---: |
| ESP32-C3-SuperMini | 1 | [Link](https://www.aliexpress.com/item/1005012360163913.html) | $2.80 |
| CZL-601 Aluminum Alloy 100kg Load Cell | 1 | [Link](https://www.aliexpress.com/item/1005004517640674.html) | $10.80 |
| HX711 Module | 1 | [Link](https://www.aliexpress.com/item/1005012556862880.html) | $4.00 |
| 2.54mm Pitch Female Pin Header Strip 5P | 10 | [Link](https://www.aliexpress.com/item/1005003610378386.html) | $2.60 |
| Micro-USB Cable | 1 | [Link](https://www.aliexpress.com/item/1005006330415728.html) | $1.60 |
| 5V / 2A Phone Charger | 1 | [Link](https://www.aliexpress.com/item/1005007670822273.html) | $2.00 |
| 3D Case | 1 | [Link](https://epro.pk/product/waterproof-electronic-enclosure-box-150x110x75mm-4x6x3-inch-in-pakistan/) - Can be 3D Printed also | $2.00 |
| PCB | 5 | JLCPCB | $4 |
| **TOTAL COST** | | | **$30** |
