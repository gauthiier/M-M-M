// "Pendulum" - spring-mass oscillator
//

#include <TimerOne.h>
#include <Motor.h>
float tf = 0.002; //time constant was .002
float kf = 0.2;  // spring constant was .15
float xf,vf,ff; // floating point versions of pendulum x and v and force
int x, f;  //int versions of position (from a/d) and force (to Pwm)
int duty; // abs(f)
byte c=0;  //counts up until 0 then prints

float m = 0.3;
float k = 0.01;

float damp = 0.09;

byte incomingByte;



void setup() 
{
  //Timer1.initialize(64); //64 microsecond period
  MotorA.torque(100); //initializes Timer1, pinModes
  Serial.begin(9600);
}

void loop(){
  x = analogRead(0); // position [0-1024]
  ff = kf*(x - xf); // spring
  f = max(ff,-1024);
  f = min(f,1024);
 // if(f>0)digitalWrite(DIRA,HIGH);
 // else digitalWrite(DIRA,LOW);
  duty = abs(f);
 // Timer1.pwm(9,duty);
  MotorA.torque(duty);
  if(f>0)MotorA.direction(FORWARD);
  else MotorA.direction(BACKWARD);
  
  // update (integrate) floating versions of xf and vf
  //integrate twice tf is deltaT/mass;
  vf += ff*tf;
  xf += vf*tf;
  
  if(c++==0) // when c gets to 255 it's next == 0 and sends data
  {
    Serial.print(x);
    Serial.print(" ");
    Serial.print(xf);
    Serial.print(" ");
    Serial.println(ff);
  }
  
if (c++ == 0)Serial.println(x); //
  if (Serial.available() > 0) {
    //Serial.print(v);
    //Serial.print(" ");
    //Serial.println(x);
    incomingByte = Serial.read();
    //Serial.write(incomingByte);
    if(incomingByte == '\''){
      m = m * 1.1;
      Serial.println(m);
    }
    if(incomingByte == ';'){
     m = m / 1.1;
     Serial.println(m);
    }
    if(incomingByte == '.'){
      k = k / 1.1;
      Serial.println(k);
    }
    if(incomingByte == '/'){
      k = k * 1.1;
      Serial.println(k);
    }
  }
}
