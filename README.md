# Pwnagotchi-NDS
Pwnagotchi port for Nintendo DS

![image](https://user-images.githubusercontent.com/4979202/221037302-eed90871-0e59-421a-bc68-c992dad73d9d.png)


# Description

This project consists of bringing Pwngotchi to the Nintendo DS

The main objective is to be able to implement a Wireless pentest tool for the Nintendo DS choosing Pwngotchi as an idea,
an AI that is dedicated to capturing

For this project, it is necessary to use an external ESP8266 since the wireless antenna of the Nintendo DS does not allow injections.
To communicate the DS with the ESP8266 the SPI bus is used, because, being a standard, its implementation in Arduino is easier.

The ESP8266 will only serve to observe the available networks and their devices, deauthenticate and capture handshakes, the AI will be inside the DS.

# Requirements

- DevkitPro Installed
- Arduino installed
- ESP8266
- Nintendo DS

# First steps

1. Compile the NDS game using DevkitPro LibNDS sdk to generate the .nds file.
2. Compile and upload the Arduino Sketch in ESP8266 folder.
3. Load the .nds game into a retail Nintendo DS using a flashcard such as R4.
4. Enjoy!

# Things to do
- Capture handshakes
- Integrate the pwnagotchi with the Nintendo DS Wifi Antenna (remove ESP8266)
