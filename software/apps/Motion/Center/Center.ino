//Center
//uses a variable force (pwm duty)
//If it feels like a mountain - pushing away from center, then
//reverse the motor leads
//or for a quick fix in the code: change if(f < 0) to if (f > 0)

#include "Motor.h"
#include "Music.h"

int pos;    // position from analogRead
int force;  // computed from pos and k
int k = 2;  // spring constant
int duty;   // pwm duty for Timer1 (range 0 - 1023) 10-bit resolution
 
void setup() 
{
  MotorA.init();
  Music.init();  
  
}

void loop() 
{

  pos = analogRead(A0);
  
  Music.setFrequency(pos);
  
  force = k * (512 - pos);
  //duty = abs(force);
  //duty = min(512, duty);
  
  MotorA.torque(force);
  
  //if(force < 0) MotorA.direction(FORWARD);
  //else MotorA.direction(BACKWARD);
    
}
  
