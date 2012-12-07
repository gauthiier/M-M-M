//Center
//uses a variable force (pwm duty)
//If it feels like a "mountain" - pushing away from center, then
//reverse the motor leads to make it feel like a "valley"
//or for a quick fix in the code: change if(f < 0) to if (f > 0)

#include <Motor.h>

int pos;    // position from analogRead
int force;  // computed from pos and k
int k = 1;  // spring constant
int duty;   // pwm duty for Timer1 (range 0 - 1023) 10-bit resolution
 
void setup() 
{
  
  MotorB.torque(100);  //is this necessary?
  
}

void loop() 
{

  pos = analogRead(A3);
  
  force = k * (512 - pos);
  duty = abs(force);
  duty = min(1023, duty);
  
  MotorB.torque(duty);
  
  if(force < 0) MotorB.direction(FORWARD);
  else MotorB.direction(BACKWARD);
    
}
  
