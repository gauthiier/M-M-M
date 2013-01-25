//Center
//uses a variable force (pwm duty)
//If it feels like a mountain - pushing away from center, then
//reverse the motor leads
//or for a quick fix in the code: change if(f < 0) to if (f > 0)

#include "Motor.h"
#include "Music.h"

int posA, posB;    // position from analogRead
int forceA, forceB;  // computed from pos and k
int kA = 2;  // spring constant
int kB = 2;  // spring constant
//int duty;   // pwm duty for Timer1 (range 0 - 1023) 10-bit resolution
 
void setup() 
{
  MotorA.init();
  Music.init();  
  Music.setWaveform(0); // only works with 8bit waveforms
}

void loop() 
{

  posA = analogRead(A0);
  posB = analogRead(A3);
  
  Music.setFrequency1(posA);
  Music.setFrequency2(posB);
  
  forceA = - kA * (512 - posA);
  forceB = kB * (512 - posB);
  //duty = abs(force);
  //duty = min(512, duty);
  
  MotorA.torque(forceA);
  MotorB.torque(forceB);
  
  //if(force < 0) MotorA.direction(FORWARD);
  //else MotorA.direction(BACKWARD);
    
}
  
