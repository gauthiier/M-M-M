// The Music object is automatically instantiated when the header file is
// included. Make calls to the Music objects with "Music.function(args)".
// You still need to call Music.init() in the setup() function below.
#define NUM_OSCILLATORS 3
#define BIT_DEPTH 8
#define MIDI
#define MIDI_CHANNEL 1
#include <Music.h>

long timeNow = 0;
long lastTime = 0;
long delayTime = 400; //in milliseconds

void setup() {

  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();
  Music.enableEnvelope();
  Midi.init();

}

void loop() {
  
  // In order to send MIDI to the sketch, use the Music_Controls_4.pde Processing sketch
  Midi.checkMidi();
  
  // The below code is an example of triggering the noteOn function to play some sounds
  timeNow = millis();
  if((timeNow - lastTime) > delayTime) {
    Music.noteOn(64);
    lastTime = timeNow;  
    
  }  
}

