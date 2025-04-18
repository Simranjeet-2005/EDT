SafeStep: Obstacle and Emergency Locator

Team

Waseem Akram

Simranjeet Kaur

Sejal

Komal


Mentor: Khushal Thakur


SafeStep is a low-cost, wearable assistive device designed to enhance mobility and safety for visually impaired individuals. It combines real-time obstacle detection with an emergency location notification system, providing both proactive and reactive safety features in a compact design.

Table of Contents

Overview

Features

Hardware Used

Software

How It Works

Results

Future Improvements

Team

License



---

Overview

SafeStep integrates:

Ultrasonic sensing for object detection with buzzer alerts.

GPS tracking and SMS alert capabilities using a push button for emergencies.

ESP32 microcontroller for seamless sensor communication and control.


This system is designed to provide real-time awareness of the user’s environment and a quick method of alerting caregivers or emergency contacts in distress situations.


---

Features

Obstacle Detection: Alerts the user when objects are within a set distance using ultrasonic sensors.

Emergency Notification: Sends an SMS with live GPS coordinates to a predefined contact via SIM800L.

Portable & Rechargeable: Powered by a 3.7V Li-ion battery with a TP4056 module for safe charging.

Low Power Design: Optimized for energy efficiency using ESP32 sleep modes and modular power cycling.



---

Hardware Used

ESP32 Development Board

HC-SR04 Ultrasonic Sensor

NEO-6M GPS Module

SIM800L GSM Module (with SIM card)

TP4056 Charging Module

3.7V Li-ion Battery

Buzzer

Push Button

Breadboard & Jumper Wires



---

Software

Arduino IDE

Libraries:

TinyGPS++ – for GPS data parsing

SoftwareSerial – for SIM800L communication (if required)




---

How It Works

1. Obstacle Detection:

The ultrasonic sensor checks for obstacles.

If an object is detected within 50cm, the buzzer emits an audible alert.



2. Emergency Alert:

User presses a button in distress.

ESP32 gets the GPS location and formats an SMS.

SIM800L sends an emergency message to a stored phone number.



3. Power Control:

Powered by a rechargeable battery.

Deep sleep and duty cycling enhance efficiency.





---

Results

Accurate Obstacle Sensing with varying buzzer intensity depending on distance.

Reliable Emergency SMS Alerts with correct GPS data and robust button debounce logic.

Modular Design successfully handled sensor data, GPS parsing, and GSM communication concurrently.



---

Future Improvements

Replace breadboard with custom PCB.

Add features like fall detection using accelerometers.

Use LoRa or NB-IoT for extended communication range.

Include vibration or LED feedback for better UX.

Waterproof and ergonomic casing.



---

Team

Waseem Akram

Simranjeet Kaur

Sejal

Komal


Mentor: Khushal Thakur


---

License

This project is for academic and non-commercial use. Reach out to contributors for collaboration or reuse permissions.
