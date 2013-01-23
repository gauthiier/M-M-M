//////////////////////////////////////////////////////////
// CIRCUIT BENDING
// This came about by accident.
// Upload the code to your board, plug into loud speakers
// and touch the bare pins to make some awesome noise :D
//////////////////////////////////////////////////////////

#include <stdint.h>
#include <Music.h>


float s;
float frequency = 220.0;
float detune = 0.01;
float bend = 0.0;

void setup(){
  
  Serial.begin(9600);
  
  Music.init();
  
  Music.setSaw();
  Music.setDetune(detune);
  Music.setFrequency(220);
  
}

void loop() {
  
   s = analogRead(0);
   bend = mapFloat(s, 0.0, 1023.0, -2.0, 2.0);
   Music.pitchBend(bend);
   frequency = Music.getNoteFrequency(48);
   //Serial.println(frequency);
   //delay(100);
  
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

