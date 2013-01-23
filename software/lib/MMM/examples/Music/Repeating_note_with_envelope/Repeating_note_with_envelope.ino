
// This needs to be in all sketches at the moment
#include <stdint.h>

// The Music and Midi objects are automatically instantiated when the header file is included.
// Make calls to the Music and Midi objects with "Music.function(args)" and "Midi.function(args)"
// You still need to call Music.init() and Midi.init() in the setup() function below.
#include <Music.h>

// variables for this sketch
boolean noteIsOn = false;
int note = 48;

long time = 0;
long lastTime = 0;
long beatTime = 1000;


void setup() {

  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();
  
  // enabling the envelope lets us define an gain envelope for the synth
  // without having to specify it in our loop() or physics code.
  Music.enableEnvelope();
  Music.setAttack(4);
  Music.setDecay(64);
  Music.setSustain(64);
  Music.setRelease(64);
  
}

void loop() {
  
  // This short routine loops note over and over again
  time = millis();
  if(time - lastTime > beatTime) {
    if(!noteIsOn) {
      Music.noteOn(note);
      noteIsOn = true;
    } else {
      Music.noteOff();
      noteIsOn = false;
    }
    lastTime = time;
  }

}

