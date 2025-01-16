# ESP8266-Wireless-Car-Control

Overview
This project demonstrates a wireless car control system using ESP8266 NodeMCU and ESP-NOW. The system uses three NodeMCUs:

Two transmitters to send joystick values (X and Y axis)
One receiver to control the car's motors
The joystick values are transmitted wirelessly from the transmitters to the receiver, which then controls the car's movement (forward, backward, left, right) accordingly.

Components Used
3 x ESP8266 NodeMCU
1 x Motor Driver (L298N or similar)
2 x DC Motors
1 x Joystick Module
Jumper wires and breadboard (for wiring)
Features
Real-time wireless communication using ESP-NOW
Independent control of X and Y axis using two NodeMCUs
Modular and scalable design
Code Description
Receiver (Motor Control)
The receiver NodeMCU listens for data from the two transmitters and controls the motors accordingly based on the received joystick values.

Transmitter (X Axis)
This NodeMCU reads the X-axis value from the joystick and sends it to the receiver. The value is transmitted using ESP-NOW.

Transmitter (Y Axis)
This NodeMCU reads the Y-axis value from the joystick and sends it to the receiver. The value is also transmitted using ESP-NOW.

How to Use
Clone or download the repository.
Open the code files in Arduino IDE.
Upload the corresponding code to each ESP8266 NodeMCU:
Upload the Receiver code to the NodeMCU that will control the motors.
Upload the Transmitter X Axis code to the NodeMCU that will control the joystick's X axis.
Upload the Transmitter Y Axis code to the NodeMCU that will control the joystick's Y axis.
Make sure all ESP8266 modules are powered up and within range of each other.
Test the system by moving the joystick, and the car will move accordingly!
License
This project is open-source. Feel free to modify and use the code for your personal or educational purposes.
