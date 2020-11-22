# Elegoo-Smart-Car
Elegoo Smart Car Library contains motion, sensors, Bluetooth and IR routines along with a main program that incorporates the enhanced program examples that came with car kit.

I was tired of re-coding the routines that enables the motors and make the car go so I created a library for them and then added routines for all the other functions on the car. 
(Line following still needs to be added.) 

The code implements 3 speeds (slow, medium and fast), 3 turning angles (20 deg, 45 deg and 90 degrees), and single straight ahead scan or continuous 3 angle scan.
It can be controled by the Infra Red remote or by Bluetooth using the Elegoo BLE Tool App on a smart phone or a tablet.

All the GPIO pins except A0, A1, A2 and A3 on the Elegoo UNO that came with the car are used up by the motors and sensors. I am currently working on adding an ESP32S 
as a master controller to allow more sensors, commands and control possibilities. (See ESP32S repository)

A couple of future add-ons include wheel encoder sensors to give better speed and turning angle control and IR sensors to help with collision avoidance.

