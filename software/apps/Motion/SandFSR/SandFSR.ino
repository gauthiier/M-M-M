#include <Motor.h>

float pos, fin, finmax, fout;
byte c; // used as a counter from 0 to 255
int duty;

void setup(){
  digitalWrite(A4,HIGH);
  digitalWrite(A5,LOW);
  pinMode(A4, INPUT);
  pinMode(A5, OUTPUT);
  //MotorB._period(32);
}

void loop(){
  fin += .01*(analogRead(A4)-fin);
  fout = 0.5*fin*(1024+random(1024));
  duty = min(1024,fout);
  duty = abs(duty);
  //duty = min(duty,1024);
   MotorB.torque(duty);
  if(fout<0)MotorB.direction(FORWARD);
  else MotorB.direction(BACKWARD);
  }


