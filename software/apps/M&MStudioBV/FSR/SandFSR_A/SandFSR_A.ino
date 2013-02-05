#include "Motor.h"

int x; //position
float fin; //from hall-sensor [ wired GND to A1 ]
float fout; //force
int duty; // max 1024
byte c; // counter to send data every 256 cycles

void setup(){
  MotorA.init();
  pinMode(A1,INPUT); //used for FSR [A1 to D4]
  pinMode(4,OUTPUT); //used for FSR as GND
  digitalWrite(A1,HIGH); //enable pull-up resistor
  digitalWrite(4,LOW); //GND for FSR
  //TimerOne
  Serial.begin(9600);
}

void loop(){
  fin =  analogRead(A1) - 1000;
  //fout = random(fin);
  fout = 2*fin + random(fin); // range [0,4096];
  fout = fout/3;
  MotorA.torque(fout);
 // Timer1.pwm(9,duty); //output force

  if(c++==0){
  Serial.print(fin);
  Serial.print(" ");
  Serial.println(fout);
  }
}

