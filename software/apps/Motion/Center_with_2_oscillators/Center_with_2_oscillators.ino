//Center two motors control two frequencies. (jb&bv 25Jan13)
//uses a variable force (pwm duty)
//If it feels like a mountain - pushing away from center, then
//reverse the motor leads or the sign of forceA or forceB
//or for a quick fix in the code: change if(f < 0) to if (f > 0)

// notes to me (bv)

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
  Music.init();  // 12-bit sine default (see .cpp file)
  //Music.setWaveform(0); // only works with 8bit waveforms
}

void loop() 
{

  posA = analogRead(A0);
  posB = analogRead(A3);
  
  Music.setFrequency1(posA);
  Music.setFrequency2(posB);
  
  forceA = - kA * (512 - posA); // check wiring???
  forceB = kB * (512 - posB);
  
  MotorA.torque(forceA); // forceA [-512 to +511] ???
  MotorB.torque(forceB);
    
}
  
