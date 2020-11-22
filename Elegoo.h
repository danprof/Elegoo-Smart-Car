//Elegoo.h
#ifndef Elegoo_h
#define Elegoo_h

#include "Arduino.h"
#include <Servo.h>;
extern Servo myservo;

class Elegoo 
{

  #define ENA 5
  #define ENB 6
  #define IN1 7
  #define IN2 8
  #define IN3 9
  #define IN4 11
  #define LED 13
  #define RECV_PIN 12
  #define Echo  A4  
  #define Trig  A5

private:
   bool state = LOW;
   int fast_speed = 150;
   int med_speed = 100;
   int slow_speed = 75;
   int motorSpeed = med_speed;
   int rightDistance = 0;
   int leftDistance = 0;
   int middleDistance = 0;

public:
   // variables
   char lastDirection;
   boolean sMode = 1;      // scan mode(0=single, 1=continuous)

   // functions
   void car_init();
   void Forward(int);
   void Back(int);
   void Left(int);
   void Right(int);
   void stopCar();
   void stateChange();
   char execute(char);
   void irCommand(int code);
   int Distance_test();
   void check_for_obstacle();
   void scanMode();



};   // end of class Elegoo

#endif