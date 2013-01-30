//Center
//uses a variable force (pwm duty)
//If it feels like a mountain - pushing away from center, then
//reverse the motor leads
//or for a quick fix in the code: change if(f < 0) to if (f > 0)

//#define NUM_OSCILLATORS 3
//#include "config.h"
#include <Motor.h>
#include <Music.h>
#include <Midi.h>


int posA, posB;    // position from analogRead
int forceA, forceB;  // computed from pos and k
int kA = -5;  // spring constant
int kB = 1;  // spring constant
//int duty;   // pwm duty for Timer1 (range 0 - 1023) 10-bit resolution
 
void setup() 
{
  MotorA.init();
  Music.init();  
  Music.setWaveform(1); // only works with 8bit waveforms
  //Music.setGain2(0);
  //Music.setGain3(0);
  Midi.init();
}

void loop() 
{

  posA = analogRead(A0);
  posB = analogRead(A3);
  
  Music.setFrequency1(posA);
  Music.setFrequency2(posB);
  //Music.setDetune((posB/8)/5120.0);
  
  forceA = kA * (512 - posA);
  forceB = kB * (512 - posB);
  //duty = abs(force);
  //duty = min(512, duty);
  
  MotorA.torque(forceA);
  MotorB.torque(forceB);
  
  Midi.checkMidi();

    
}
  
