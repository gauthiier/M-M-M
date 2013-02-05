//"Pulse" - small duration positive then negative force 
// parameters: F1, T1, D1, F2, T2, D2

#define BIT_DEPTH 12

#include <Motor.h>
#include <Music.h>

void setup(){
  MotorB.init();
  Music.init();
  
  Music.setWaveform(SINE);
  Music.enableEnvelope();
  Music.setAttack(10);
  Music.setDecay(10);
  Music.setRelease(10);
}

void loop(){
  //for (int i; i < 512; i + 100){
    MotorB.torque(40);
    Music.noteOn(map(analogRead(A3),0,1023,30,60));
    delay (20);
    Music.noteOff();MotorB.torque(0);
    delay (150);
    MotorB.torque(-70);
    Music.noteOn(map(analogRead(A3),0,1023,35,65));
    delay (40);
    Music.noteOff();MotorB.torque(0);
    MotorB.torque(0);
    delay (750);
  //}
}
