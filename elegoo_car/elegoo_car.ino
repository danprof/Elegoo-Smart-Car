//*************************
//* Elegoo_car
//*
//* Control using ELEGOO BLE App on phone
//* connect to HC-08
//*
//* or use IR remote
//*
//*************************
// Author:       Daniel Nadeau
// Last Revised: Nov 11, 2020

#include <Servo.h>
Servo myservo;   // create instance of servo

#include "Elegoo.h"
Elegoo robot;   // create instance of car
#include <IRremote.h>




//int RECV_PIN = 12;        // InfraRed receive pin defined in Elegoo.h
IRrecv irrecv(RECV_PIN);
decode_results results;


char getByte;    // serial input buffer
char ld = 's';   // last direction indicator
 

//int Echo = A4;  
//int Trig = A5;

//---------------------
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("\n\n\n\n\n\n\n\n\n");
  if (Serial){
     Serial.println("Serial Communication Active");
  }
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the Infra Red receiver
  Serial.println(" - Infrared Enabled");
  Serial.println("Initializing Car ");
  Serial.print(" - Motion set to ");
  robot.car_init();
  Serial.println(" - Car initialized"); 
   
  myservo.attach(3);  // attach servo on pin 3 to servo object
  myservo.write(0);   // move servos to center position -> 0°
  delay(500);
  myservo.write(90);  // move servos to center position -> 90°
  Serial.println(" - Servo centered");
  Serial.println("Ready");

  pinMode(Echo, INPUT);   // setup sonar 
  pinMode(Trig, OUTPUT);
}

//-------------------------------------------

void loop(){
// check for obstacles when moving Forwards  
    if(robot.lastDirection == 'f'){
      robot.check_for_obstacle();
    }
    
//------------- receive Bluetooth data ---------

    if (Serial.available() > 0) {
       // read the incoming byte:
       getByte = Serial.read();	// read keyboard or BlueTooth command
       Serial.print("getByte = ");
       Serial.println(getByte);
       if( getByte != ld){
          ld = robot.execute(getByte);
          Serial.println(ld);
       }
    }
    
//-------------- receive Infra Red data -----------

    if (irrecv.decode(&results)) {
        Serial.print(results.value, HEX);
        Serial.print(" - ");
        Serial.println(results.value, DEC);
    
        robot.irCommand(results.value);

        irrecv.resume(); // Receive the next value
  }

}
