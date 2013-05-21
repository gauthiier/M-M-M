//FM synthes of a sort
<<<<<<< HEAD:software/lib/MMM/examples/Motion/_8_FM/_8_FM.ino
//hang on! (it's unstable and wants to limit cycle)
=======
//hang on!  it's unstable and wants to limit cycle

#define BIT_DEPTH 8 // gives us 16 Waveforms
>>>>>>> getting FM:software/apps/Modeling/FM/FM.ino

#include <Music.h>

#include <Motor.h>

byte cnt;
float xf, vf; //
float k = 10.0; // increase FM frequency
float b = 0.40; // increase
float Tf = .030 ; //integration time

void setup(){
  Serial.begin(9600);
  Music.init();
  Music.setWaveform(0);
  Music.setGain(1.0f);
  MotorA.init();
}

void loop(){
  xf += vf * Tf;
  vf += (k * (analogRead(A0) - xf) - b*vf) * Tf;
  Music.setFrequency(100+vf);
  Music.setGain(.001*abs(vf));
  MotorA.torque(-500+xf);
  //if(cnt++==0)Serial.println(.001*abs(vf));
}
