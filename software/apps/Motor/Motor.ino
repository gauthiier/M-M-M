//#include <TimerOne.h>
//BV 24Jan13

#include <Motor.h>

void setup() 
{
  MotorA.init();
  MotorA.torque(500);  //512 is max torque
  
}

void loop() 
{

  MotorA.direction(FORWARD);
  delay(1000);
  MotorA.direction(BACKWARD);
  delay(1000);  
  
}
  
