# V.A.H.T.I
### Description
An Arduino Mega & ESP3822 School project, which gathers data a rotating ultrasound sensor, displays data on an lcd screen and sends an alarm through ESP3822 to an email address using IFTTT Webhook. A school project for first semester.

### Prerequisites
- Arduino Mega
- <a href="https://www.arduino.cc/en/software">Arduino IDE itself (I recommend using 1.8.xx IDE as I've had problems with ESP3822 using 2.0.xx)</a>
- <a href="https://arduino-esp8266.readthedocs.io/en/latest/installing.html">Arduino IDE ESP8266 Board Manager and it's own Prerequisites</a>
- ESP3822 (any module works, but we used ESP-01S)
  - <sub>IF using ESP-01/ESP-01S, a way for the computer and ESP to communicate, we recommend using an USB-ESP01 adapter, spares some headaches.</sub>
  - <sub>IF using ESP-01, remember to get extra ~12k ohm resistors to pull-up GPIO0, GPIO2, RST and EN pins.</sub>
- Arduino compatible 16*2 LCD-screen
- Arduino compatible servomotor
- Ultrasound sensor
- 2 5v to 3.3v voltage regulators
- 2 100nF capacitators
- 2 10µF capacitators
- 10k ohm resistor
- 220 ohm resistor
- 10k ohm potentiometer
- RFID-RC522 RFID reader and a RFID tag

### Instalation guide
![Vahti](https://github.com/SakRoi/V.A.H.T.I/blob/main/vahti.png)
