//Elegoo.cpp

#include "Arduino.h"
#include "Elegoo.h"           // Dan's robot car library header


//------------------------------
void Elegoo::car_init(){		// initialize pins to output
  pinMode(ENA,OUTPUT);			// motor control
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(LED, OUTPUT);			// Builtin LED
  pinMode(LT_R,INPUT);			// line tracking sensors
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);

  stopCar();
  for(int i=1; i<4; i++){		
     digitalWrite(LED, HIGH);		// blink led 3 times
     delay(1000);
     digitalWrite(LED, LOW);
     delay(1000);
  }
  sMode = 1;				// set default scan mode to continuous
}

//------------------------------
void Elegoo::Forward(int carSpeed){ 	//go forward
  Serial.println("Forward");
  digitalWrite(ENA,HIGH);		// initial start
  digitalWrite(ENB,HIGH);
  delay(50);
//  stopCar();
  analogWrite(ENA,carSpeed);		// adjust speed
  analogWrite(ENB,carSpeed);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
//------------------------------
void Elegoo::Back(int carSpeed){	// back up
  Serial.println("Back");
  digitalWrite(ENA,HIGH);		// initial start
  digitalWrite(ENB,HIGH);
  delay(50);
  analogWrite(ENA,carSpeed);		// adjust speed
  analogWrite(ENB,carSpeed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
//------------------------------
void Elegoo::Left(int degree){		// turn left 20 or 45 or 90 degrees
  digitalWrite(ENA,HIGH);		// full speed for turns
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  Serial.println("Left");		 
  switch (degree){
    case 20:
	delay(150); break;
    case 45:
	delay(250); break;
    case 90:
	delay(375); break;
  }

  execute(lastDirection);
}
//------------------------------
void Elegoo::Right(int degree){		// turn right 20 or 45 or 90 degrees
  digitalWrite(ENA,HIGH);		// full speed for turns	
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Right");
  switch (degree){
    case 20:
	delay(150); break;
    case 45:
	delay(250); break;
    case 90:
	delay(375); break;
    }

  execute(lastDirection);
}
//------------------------------
void Elegoo::stopCar(){			//stop car
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("Stop!");
  return ;
}
//------------------------------
void Elegoo::stateChange(){		// toggle light
  state = !state;
  digitalWrite(LED, state);
  Serial.println("Light");  
}
//------------------------------
char Elegoo::execute(char getstr){	// execute received command

 switch(getstr){
    case 'f': Forward(motorSpeed); lastDirection = 'f';break;
    case 'b': Back(motorSpeed); lastDirection = 'b';  break;
    case 's': stopCar(); lastDirection = 's';  break;
    case 'j': Left(20);   break;
    case 'k': Left(45);   break;
    case 'l': Left(90);   break;
    case 'p': Right(20);  break;
    case 'q': Right(45);  break;
    case 'r': Right(90);  break;
    case 'a': stateChange(); break;
    case '1': motorSpeed = slow_speed; execute(lastDirection); break;
    case '2': motorSpeed = med_speed; execute(lastDirection); break;
    case '3': motorSpeed = fast_speed; execute(lastDirection); break;
    case '#': scanMode(); 
    default:  break;
  }
Serial.print("------");
Serial.println(lastDirection);
return lastDirection;
}

//------------------------------

// Ultrasonic distance measurement Sub function

int Elegoo::Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58; 
//duration = pulseIn(Echo, HIGH); 
// Fdistance= duration*0.034/2;    // try this later  
  return (int)Fdistance;
} 

//------------------------------
void Elegoo::check_for_obstacle(){
   int md1;
   if(sMode == 1){	 // ------ continuous side to side scan -------
 
      for(int i=1; i>0; i--){
         md1 = Distance_test();    // get right of middle distance
         Serial.print("     ");
         Serial.println(md1);
         if(md1 <= 20) break;
      
         myservo.write(120);          
         delay(200);
         md1 = Distance_test();    // get left distance
         Serial.print("<");
         Serial.println(md1); 
         if(md1 <= 20) break; 
                
         myservo.write(90);          
         delay(200); 
         md1 = Distance_test();    // get middle distance 
         Serial.print("     ");
         Serial.println(md1);
         if(md1 <= 20) break;
      
         myservo.write(60);          
         delay(200);
         md1 = Distance_test();    // get right distance
         Serial.print("          >");
         Serial.println(md1); 
         if(md1 <= 20) break; 
                
         myservo.write(90);          
         delay(200); 
         md1 = Distance_test();    // get middle distance 
         Serial.print("     ");
         Serial.println(md1);
         if(md1 <= 20) break;
      }
    }  
   if(sMode == 0){        //--------- Single forward scan ----------------

         md1 = Distance_test();    // get middle distance
         delay(100); 

         Serial.print(" distance: ");
         Serial.println(md1);       
    }                
             //--------- if object detected, turn ---------

   if(md1 <= 20) {                   
      stopCar();
      delay(2000); 
                              
      myservo.write(30);                // get right distance         
      delay(1000);      
      rightDistance = Distance_test();   
      Serial.print("right distance: ");
      Serial.println(rightDistance);
                                           
      myservo.write(180);               // get left distance              
      delay(1000); 
      leftDistance = Distance_test();
      Serial.print("left distance: ");
      Serial.println(leftDistance);
      myservo.write(90);

      if(rightDistance > leftDistance) {
        Right(45);
       }
      else if(rightDistance < leftDistance) {
        Left(45);
      }
      else if((rightDistance <= 20) && (leftDistance <= 20)) {
        Back(20);
        delay(1000);
        Right(90);
        Right(90);
      }
   }             
}

//------------------------------
void Elegoo::scanMode(){
   sMode = !sMode;             // toggle scan mode between single and continuous 
   Serial.println("Scan Mode changed ");
  
}
//------------------------------
void Elegoo::irCommand(int ircode){

    switch (ircode){
      case 0xFF629D: Serial.println(" up "); digitalWrite(13,HIGH); execute('f'); break;    //Forward
      case 0xFFA857: Serial.println(" down "); digitalWrite(13,HIGH);execute('b'); break;   //Reverse
      case 0xFF22DD: Serial.println(" left "); digitalWrite(13,HIGH);execute('l'); break;   //L90 (90 degree left turn)
      case 0xFFC23D: Serial.println(" right "); digitalWrite(13,HIGH);execute('r'); break;  //R90 (90 degree right turn) 
      case 0xFF02FD: Serial.println(" ok "); digitalWrite(13,HIGH);execute('s'); break;     //Stop
      case 0xFF6897: Serial.println(" 1 "); digitalWrite(13,HIGH); execute('1');break;      // speed Slow
      case 0xFF9867: Serial.println(" 2 "); digitalWrite(13,HIGH); execute('2');break;      // speed Medium
      case 0xFFB04F: Serial.println(" 3 "); digitalWrite(13,HIGH); execute('3');break;      // speed Fast
      case 0xFF30CF: Serial.println(" 4 "); digitalWrite(13,HIGH);execute('j'); break;      //L20 (20 degree left turn)
      case 0xFF18E7: Serial.println(" 5 ");  digitalWrite(13,HIGH); break; 
      case 0xFF7A85: Serial.println(" 6 "); digitalWrite(13,HIGH);execute('p'); break;      //R20 (20 degree right turn) 
      case 0xFF10EF: Serial.println(" 7 ");  digitalWrite(13,HIGH);execute('k'); break;     //L45 (45 degree left turn)
      case 0xFF38C7: Serial.println(" 8 "); digitalWrite(13,HIGH); break;  
      case 0xFF5AA5: Serial.println(" 9 "); digitalWrite(13,HIGH);execute('q'); break;       //R45 (45 degree right turn)
      case 0xFF4AB5: Serial.println(" 0 "); digitalWrite(13,HIGH); break; 
      case 0xFF42BD: Serial.println(" * "); digitalWrite(13,HIGH); execute('a');break;       // light
      case 0xFF52AD: Serial.println(" # "); digitalWrite(13,HIGH); execute('#');break;	     // toggle scan mode between single and continuous

   default:
         Serial.println("UNKNOWN CODE");
         break;                
    }
    digitalWrite(13,LOW);  
    return;
} 




//------------------------------
