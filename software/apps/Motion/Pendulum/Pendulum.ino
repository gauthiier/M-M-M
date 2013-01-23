// "Pendulum" - spring-mass oscillator
#include <Motion.h>
#include <Motor.h>

byte incomingByte;

void setup() 
{
  // init MotionA & MotorA
  MotionA.init(INPUTA0);
  MotorA.init();

  // provide MotionA with initial physics constants
  MotionA.k = 0.2f;   // spring
  MotionA.m = 0.3f;   // mass
  MotionA.d = 0.02f;  // damping
  
  Serial.begin(9600);
}

void loop(){
  
  if(MotionA.F < 0) MotorA.direction(FORWARD);
  else MotorA.direction(BACKWARD);
  
  float t = abs(MotionA.F);
  //if(t > 512) t = 512;
  //MotorA.torque(t);

  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if(incomingByte == '1'){
      MotionA.m = MotionA.m * 1.1;
      Serial.print("m: ");
      Serial.println(MotionA.m);
    }
    else if(incomingByte == '!'){      
      MotionA.m = MotionA.m / 1.1;
      Serial.print("m: ");
      Serial.println(MotionA.m);
    }    
    else if(incomingByte == '2'){
     MotionA.k = MotionA.k * 1.1;
     Serial.print("k: ");
     Serial.println(MotionA.k);
    }
    else if(incomingByte == '@'){
     MotionA.k = MotionA.k / 1.1;
     Serial.print("k: ");
     Serial.println(MotionA.k);
    }    
    else if(incomingByte == '3'){
      MotionA.d = MotionA.d * 1.1;
      Serial.print("d: ");
      Serial.println(MotionA.d);
    }
    else if(incomingByte == '#'){
      MotionA.d = MotionA.d / 1.1;
      Serial.print("d: ");
      Serial.println(MotionA.d);
    }    
  }
}
