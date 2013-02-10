//CenterFSR-A
//position on A0, pwm:D9, dir:D8,D7
//FSR on A1 and D4

// BUZZ! (float vs int?)
#include "Motor.h"

int x, duty, fin;
float fout;
byte count; // used as counter

void setup(){
  Serial.begin(9600);
  MotorA.init();
  //for FSR
  pinMode(A1,INPUT);
  digitalWrite(A1,HIGH);
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
}

void loop(){
  fin = 1024 - analogRead(A1);
  x = analogRead(A0)-512;
  fout = - .004*(float(fin)*float(x));
  MotorA.torque(fout);
  if(count++ == 0){
    Serial.print(x,DEC);
    Serial.print(" ");
    Serial.print(fin,DEC);
    Serial.print(" ");
    Serial.println(fout,DEC);
  }
}  
