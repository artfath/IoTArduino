# IoTArduino Smart Lamp

## Overview
a simple project IoT use ESP32 with dimmer AC lamp to control brightness lamp. Dimmer AC lamp use zerocross pin to detect
0 VAC and PWM pin to make PWM signal with dutycycle. in ESP32 progamming, ESP32 use external interrupt to detect 0 VAC and 
timer interrupt used to generate PWM signal. to connecting on firebase, this project use library <ArduinoJson.h> and <FirebaseESP32.h>.

## Hardware Required

1 x Robotdyn AC Dimmer Module, 1 Channel, 3.3V
1 x ESP32 dev doit
1 x fitting E27
1 x dimmable lamp 3 watt
4 x female-female jumper
1 x cable 2x0.75 sqmm
1 x power cable with electric plug

## Wiring Diagram



