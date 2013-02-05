//Wall
//need some mass so it "bounces"?

#include <Motor.h>
#include <Music.h>

int x;
boolean inside;
int Fout;
int wave;
int Fmax = 4023;

void setup(){
  Serial.begin(9600);
  MotorA.init();
  
  Music.init();
  Music.setWaveform(0);//8bit 0 = sine.
  Music.setGain(0.0f);
  Music.setFrequency(200);
}

void loop() {
// waiting for "return" or "line-feed"
while (Serial.available()) {
    wave = Serial.parseInt();
    if (Serial.read() == '\n') {
      Serial.print("I received: ");
      Serial.println(wave, DEC);
      if (wave > 16) wave = 16;
      if (wave < 0) wave - 0;
      Music.setWaveform(wave);
    }
  }  x = analogRead(A0)-512;
  if(x < 0){
    Fout = -20*x;
    MotorA.torque(Fout);
    Music.setGain(1.0f);  //contact silences music?
    //Music.setGain(float(x/200));
    inside = true;
  }
  else{
    if (inside){  //first time outside
      inside = false; //start note
      Music.setGain(1.0f);
    }
    if(x>10){
    Music.setGain(0.998f*Music.getGainFloat());
    }
  }
}
  
  
  
