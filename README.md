# IoTArduino Smart Lamp

## Overview
a simple project IoT use ESP32 with dimmer AC lamp to control brightness lamp. Dimmer AC lamp use zerocross pin to detect
0 VAC and PWM pin to make PWM signal with dutycycle. in ESP32 progamming, ESP32 use external interrupt to detect 0 VAC and 
timer interrupt used to generate PWM signal. to connecting on firebase, this project use library <ArduinoJson.h> and <FirebaseESP32.h>.

## Hardware Required

- 1 x Robotdyn AC Dimmer Module, 1 Channel, 3.3V
- 1 x ESP32 dev doit
- 1 x fitting E27
- 1 x dimmable lamp 3 watt
- 4 x female-female jumper
- 1 x cable 2x0.75 sqmm
- 1 x power cable with electric plug

## Wiring Diagram

| Pin ESP32    | Pin Dimmer AC Lamp | 
| :---         | :---:              | 
| 3V3          | Vcc                | 
| GND          | GND                | 
| GPIO 4       | PWM                | 
| GPIO 16      | Z-C                | 



## Documentation

<img src="https://user-images.githubusercontent.com/86766443/158057801-3d5ed697-967f-4cbd-8c9f-a15ab8f159cd.jpg" width="300"> <img src="https://user-images.githubusercontent.com/86766443/158057812-2cfd2ed6-7589-4f51-b20d-8f0acd275910.jpg" width="300"> <img src="https://user-images.githubusercontent.com/86766443/158057808-06e816d6-cac5-4904-ace4-f8f4329efb10.jpg" width="300"> <img src="https://user-images.githubusercontent.com/86766443/158057806-163562f1-2973-45cf-8650-0233472ec260.jpg" width="300"> <img src="https://user-images.githubusercontent.com/86766443/158057804-db421403-99b7-4cb7-a5fc-8fada405e797.jpg" width="300">








