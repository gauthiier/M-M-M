//motortest
//.5 sec forward, .5 sec back

#include <Motor.h>

int led = 13;

void setup() 
{ 
  MotorA.torque(511);  //what is max torque?
  pinMode(13, OUTPUT);
}

void loop()
{
  MotorA.direction(FORWARD);
  delay(500);
  MotorA.direction(BACKWARD);
  delay(500);
}
