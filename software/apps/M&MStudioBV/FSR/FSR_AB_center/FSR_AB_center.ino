// FSR A and B
// stick-slip

#include <Motor.h>
int xA, finA, foutA; //fout gets too big if fout=fin*x;
float x, fin, fout;
byte c;

void setup(){
  //FSR-A
  pinMode(A1,INPUT);
  digitalWrite(A1,HIGH); //set pull-up
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
  //FSR-B
  pinMode(A4,INPUT);
  digitalWrite(A4,HIGH); //set pull-up
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  
  //Motors
  MotorA.init();
  MotorB.init();
  
  Serial.begin(9600);
}
void loop(){
  x = 512 - analogRead(A0); //in:[0,1023] out: [-512,511]
  fin = 1024 - analogRead(A1); //in:[1023,0] out [0,1023]
  fout = x*fin/500;
  MotorA.torque(fout);

  x = 512 - analogRead(A3); //in:[0,1023] out: [-512,511]
  fin = 1024 - analogRead(A4); //in:[1023,0] out [0,1023]
  fout = x*fin/500;
  MotorB.torque(fout);
}
