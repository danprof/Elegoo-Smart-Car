//Elegoo.h
#ifndef Elegoo_h
#define Elegoo_h

#include "Arduino.h"
#include <Servo.h>;
extern Servo myservo;

class Elegoo 
{

  #define ENA 5			// left and right motor Enables
  #define ENB 6		
  #define IN1 7			// motor direction control pins
  #define IN2 8
  #define IN3 9
  #define IN4 11
  #define LED 13		// built in LED
  #define RECV_PIN 12		// IR receiver
  #define Echo  A4  		// sonar Echo
  #define Trig  A5		// sonar Trig
  #define LT_R !digitalRead(10)	//Line Tracking IO define
  #define LT_M !digitalRead(4)
  #define LT_L !digitalRead(2)

private:
   bool state = LOW;		// current drive state (forward,reverse,stop)
   int fast_speed = 150;
   int med_speed = 100;
   int slow_speed = 75;
   int motorSpeed = med_speed;
   int rightDistance = 0;	// sonar readings
   int leftDistance = 0;
   int middleDistance = 0;

public:
   // variables
   char lastDirection;
   bool sMode = 1;     		// scan mode(0=single, 1=continuous)
   bool sound = true;		// sound setting
   String opMode = "roam"; 	// default operation mode

   // functions
   void car_init();
   void Forward(int);
   void Back(int);
   void Left(int);
   void Right(int);
   void stopCar();
   void stateChange();		// toggle light
   char execute(char);
   void irCommand(int code);
   int Distance_test();
   void check_for_obstacle();
   void scanMode();



};   // end of class Elegoo

#endif