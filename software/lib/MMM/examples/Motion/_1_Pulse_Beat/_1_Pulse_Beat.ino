//"Pulse" - small duration positive then negative force 
// parameters: F1, T1, D1, F2, T2, D2

#define BIT_DEPTH 12

#include <Motor.h>
#include <Music.h>

void setup(){
  MotorA.init();
  Music.init();
  
  Music.setWaveform(SINE);
  Music.enableEnvelope();
  Music.setAttack(10);
  Music.setDecay(10);
  Music.setRelease(10);
}

void loop(){
    MotorA.torque(200);
    Music.noteOn(map(analogRead(A3),0,1023,30,60));
    delay (20);
    Music.noteOff();MotorA.torque(0);
    delay (150);
    MotorA.torque(-200);
    Music.noteOn(map(analogRead(A3),0,1023,35,65));
    delay (40);
    Music.noteOff();MotorA.torque(0);
    MotorA.torque(0);
    delay (750);
}
