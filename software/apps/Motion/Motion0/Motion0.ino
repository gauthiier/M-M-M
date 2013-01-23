#include <Motion.h>
#include <Motor.h>

/*

Two motion objects are available from the MMM Motions library
(1) MotionA
(2) MotionB

MOTION {
    MOTIONA ,
    MOTIONB1
};

Each objects needs intialisation with a specific input 
from which ADC reading will be performed.

Users may choose and identify inputs aa INPUT[A0, ... ,A7].
ex: MotionA.init(INPOUTA5);

INPUT {
    INPUTA0,
    INPUTA1,
    INPUTA2,
    INPUTA3,
    INPUTA4,
    INPUTA5,
    INPUTA6,
    INPUTA7      
}

All calculation of physics (position, velocity and acceleration) 
are computed internally usign interrupts and timers. To access
such information, user may call getPosition(), getVelocity() 
and getAcceleration() respectively on a initialised Motion object.

int getPosition();
float getVelocity();
float getAcceleration();

*/

void setup() {
  MotionA.init(INPUTA0);
  MotorA.init();
  Serial.begin(9600);
  
  MotionA.k = 0.2f;
  MotionA.m = 0.3f;
  MotionA.d = 0.02f;
  
}

void loop() {
  
  if(MotionA.F < 0) MotorA.direction(FORWARD);
  else MotorA.direction(BACKWARD);
  
  float t = abs(MotionA.F);
  MotorA.torque(t);
  
  /*
  Serial.print("position: "); Serial.println(MotionA.getPosition());
  Serial.print("velocity: "); Serial.println(MotionA.getVelocity());
  Serial.print("accel: "); Serial.println(MotionA.getAcceleration());
  Serial.println("-------");
  delay(100);
  */
}


