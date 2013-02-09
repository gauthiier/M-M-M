//plucks - four bumps
//three notes (400,500,600hz)
//can't get Music.setGain1, etc to work only Music.setGain() starts all of them.
//requires FSR attached to A

#define NUM_OSCILLATORS 3
#define BIT_DEPTH 8

#include <Music.h>
#include <Motor.h>

int x, xold, xt; // input position x, output force F
float K = 20; // slope constant
byte count; //for print count-down
float fin; // scaled to be 0.0 - 1.0
float fout; // from FSR

void setup(){
  Music.init();
  Music.setFrequency1(200);
  Music.setFrequency2(250);
  Music.setFrequency3(300);
  
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
  
  Serial.begin(9600);
  
  MotorA.init();
  
  Serial.begin(9600);
  x = analogRead(A0); // initialize x
}

void loop(){
  xold = x;
  x =  analogRead(A0);

// did xold - x include 125, 375, 625, 875?  or x%250 = 125

if (((xold <= 125) && (x > 125)) || ((xold >= 125) && (x < 125))){
  Music.setGain1(1.0);//Music.setGain1(fin*fin);
  Music.setFrequency1(200);
}
if (((xold <= 375) && (x > 375)) || ((xold >= 375) && (x < 375))){
  Music.setGain2(1.0);//Music.setGain2(fin*fin);
  //Music.setFrequency(250);
}
if (((xold <= 625) && (x > 625)) || ((xold >= 625) && (x < 625))){
  Music.setGain3(1.0);//Music.setGain3(fin*fin);
  //Music.setFrequency(300);
}
if (((xold <= 875) && (x > 875)) || ((xold >= 875) && (x < 875))){
  Music.setGain1(1.0);//Music.setGain1(fin*fin);
  Music.setFrequency1(400);
  }
  else{
    Music.setGain1(0.995f*Music.getGain1());
    Music.setGain2(0.995f*Music.getGain2());
    Music.setGain3(0.995f*Music.getGain3());
  }
  fin = 1000 - analogRead(A1); // invert and shift
  fin = max (0, fin); // make sure it's > 0
  fin = min (1023, fin); // and < 1023
  fin = fin/1000; // scale 0-1.0
  fin = fin*fin; //square it for more effect near 1.0.
  xt = x % 250; //same force for each 250 ranage
  fout = 0;
  if (xt > 60) fout = - K * (xt - 60);
  if (xt > 80) fout = - K * (100 - xt);
  if (xt > 120) fout =  K * (140 - xt);
  if (xt > 140) fout = 0;
//fout = fout * fin;
  fout = fout;
  MotorA.torque(fout);
  
 
 // print every 256 cycles
  if(count++==0){
    Serial.print(x);
    Serial.print(" ");
    Serial.print(xt);
    Serial.print(" ");
    Serial.print(fin);
    Serial.print(" ");
    Serial.println(fout);
  }

}
    
