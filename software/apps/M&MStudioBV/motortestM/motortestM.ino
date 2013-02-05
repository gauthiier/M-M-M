//motortest
//.5 sec forward, .5 sec back

#include <Motor.h>

void setup() 
{ 
  MotorA.init();
  MotorB.init();
  MotorA.torque(40);  // small force for Plank
  MotorB.torque(200);  // need 200 for Fader
}
 
void loop()
{
  MotorA.direction(FORWARD);
  MotorB.direction(FORWARD);
  delay(500);
  MotorA.direction(BACKWARD);
  MotorB.direction(BACKWARD);
  delay(500);
}
