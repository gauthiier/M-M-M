#include <Motor.h>

void setup() 
{
  MotorA.init();
  MotorA.torque(255); 
}

void loop() 
{
    MotorA.direction(FORWARD);
    delay(1000);
    MotorA.direction(BACKWARD);
    delay(1000);  
}
  
