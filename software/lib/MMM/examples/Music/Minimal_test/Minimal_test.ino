
// This needs to be in all sketches at the moment
#include <stdint.h>

// The Music and Midi objects are automatically instantiated when the header file is included.
// Make calls to the Music and Midi objects with "Music.function(args)" and "Midi.function(args)"
// You still need to call Music.init() and Midi.init() in the setup() function below.
#include <Music.h>
#include <Midi.h>

uint8_t i = 0;

void setup() {
  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();
  Music.setFrequency(110);
  Music.setGain1(1.0f);
  Music.setGain2(1.0f);
  Music.setGain3(1.0f);
  Music.setWaveform1(0);
  Music.setWaveform2(0);
  Music.setWaveform3(0);
  //Music.setDetune2(0.0015478);
  //Music.setDetune3(-0.0012894);

}

void loop() {
  
  Midi.checkMidi();
  
}

