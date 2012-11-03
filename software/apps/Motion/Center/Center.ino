//Center
//uses a variable force (pwm duty)
//If it feels like a mountain - pushing away from center, then
//reverse the motor leads
//or for a quick fix in the code: change if(f < 0) to if (f > 0)

#include <Motor.h>

int pos;    // position from analogRead
int force;  // computed from pos and k
int k = 2;  // spring constant
int duty;   // pwm duty for Timer1 (range 0 - 1023) 10-bit resolution
 
void setup() 
{
  
  MotorA.torque(100);  //is this necessary?
  
}

void loop() 
{

  pos = analogRead(A0);
  
  force = k * (512 - pos);
  duty = abs(force);
  duty = min(1023, duty);
  
  MotorA.torque(duty);
  
  if(force < 0) MotorA.direction(FORWARD);
  else MotorA.direction(BACKWARD);
    
}
  
