
# V.A.H.T.I


### Description

[TODO: add V.A.H.T.I logo here]

An Arduino Mega & ESP8266 School project. Gathers distance data with a rotating ultrasound sensor, displays data on a LCD and sends an alarm through ESP8266 to an email address using IFTTT Webhook when it notices great difference between old and new distance data. 

A school project for first semester.

  

### Prerequisites

#### Digital dependencies

-  <a  href="https://www.arduino.cc/en/software">Arduino IDE itself (I recommend using 1.8.xx IDE as there were problems with ESP8266 Board Manager using 2.0.xx)</a>

-  <a  href="https://arduino-esp8266.readthedocs.io/en/latest/installing.html">Arduino IDE ESP8266 Board Manager and it's own Prerequisites</a>

  
  #### Physical dependencies

- Arduino Mega (or equivalent)

- ESP3822 (any module works, we used ESP-01S)

-  <sub>IF using ESP-01/ESP-01S, a way for the computer and ESP to communicate, such as USB-ESP01 adapter.</sub>
-  <sub>IF using ESP-01, you also need extra ~12k ohm resistors to pullup GPIO0, GPIO2, RST and EN pins.</sub>

- Arduino compatible 16*2 LCD-screen
- Arduino compatible servomotor
- Ultrasonic distance sensor (HC-SR04)
- 2 5v to 3.3v voltage regulators
- 2 100nF capacitators
- 2 10µF capacitators
- 10k ohm resistor
- 220 ohm resistor
- 10k ohm potentiometer
- RFID-RC522 RFID reader and a RFID tag

  
### Installation guide and circuit diagram
1. Compile and upload vahti.ino source code onto Arduino Mega or equivalent.
2. Make an user for IFTTT webhook service.
3. Edit the esp8266.ino code to use the IFTTT key and connect to internet.
4. Compile and upload esp8266.ino source code onto ESP8266.
5. Build the device according to the circuit diagram.

[TODO: a good and up to date circuit diagram] 

![Vahti](https://github.com/SakRoi/V.A.H.T.I/blob/main/vahti.png)

### Roadmap
- Make arduino.ino work for multiple boards by either compile time trickery or just making multiple source codes.
- Demo video
- Circuit diagram

![Vahti](https://github.com/SakRoi/V.A.H.T.I/blob/main/vahti.png)
