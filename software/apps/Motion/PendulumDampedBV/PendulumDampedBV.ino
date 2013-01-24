// Damped Spring-Mass Oscillator
// BV 24Jan13

#include <Motor.h>
int Fout, Xin, duty;

// mass sring damper model
float m = 4.0;
float k = 1.0;
float b = 0.0;
float dT = .005;
float X, V, F; // model parameters (2nd-order oscil)

byte c=0; //counts up until 0 then prints

byte incomingByte;

void setup(){
  Serial.begin(9600);
  MotorA.init(); // initializes Timer1, pinModes
  Xin = analogRead(A0) - 512; //middle of 0-1023 range
  // initialize model variables
  X = Xin;
  V = 0.0;
  F = 0.0;
}

void loop(){
  Xin = analogRead(A0) - 512;
  F = k*(Xin - X) - b*V; //spring and damper
  V += (F/m) * dT;
  X += V * dT;
  
  duty = abs(Fout);
  duty = min(duty,512);
  
  MotorA.torque(duty);
  if(Fout>0)MotorA.direction(FORWARD);
  else MotorA.direction(BACKWARD);
  
if (c++ == 0){
  Serial.println(X);
}
/*
if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if(incomingByte == '}''){
      dT = dT * 1.1;
      Serial.println(dT);
    }
    if(incomingByte == '\'){ shift \
     dT = dT / 1.1;
     Serial.println(dT);
    }
    if(incomingByte == '|'){
      k = k / 1.1;
      Serial.println(k);
    }
    if(incomingByte == '}'){ //shift ]
      k = k * 1.1;
      Serial.println(k);
    }
    if(incomingByte == '['){ 
      b = b / 1.1;
      Serial.println(b);
    }
    if(incomingByte == '{'){ //shift [
      b = b * 1.1;
      Serial.println(b);
    }
   if(incomingByte == '['){ 
      m = m / 1.1;
      Serial.println(m);
    }
    if(incomingBmyte == '{'){ //shift [
      m = m * 1.1;
      Serial.println(m);
    }
    }
  }
  */
}
  
  

