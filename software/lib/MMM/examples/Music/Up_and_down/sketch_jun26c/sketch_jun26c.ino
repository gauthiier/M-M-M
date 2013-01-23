
// This needs to be in all sketches at the moment
#include <stdint.h>

// The Music and Midi objects are automatically instantiated when the header file is included.
// Make calls to the Music and Midi objects with "Music.function(args)" and "Midi.function(args)"
// You still need to call Music.init() and Midi.init() in the setup() function below.
#include <Music.h>

// variables for this sketch
boolean noteIsOn = false;
int n = 0;
int dir = 1;
int rootNote = 48;
int note[] = {0,2,3,5,7,9,10,12,14};

long time = 0;
long lastTime = 0;
long beatTime = 100;


void setup() {

  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();
      
  // enabling the envelope lets us define an gain envelope for the synth
  // without having to specify it in our loop() or physics code.
  Music.enableEnvelope();
  Music.setAttack(8);
  Music.setDecay(70);
  Music.setSustain(24);
  Music.setRelease(90);
  
}

void loop() {
  
  // This short routine loops note over and over again
  time = millis();
  if(time - lastTime > beatTime) {
    if(!noteIsOn) {
      Music.noteOn(rootNote+note[n]);
      noteIsOn = true;
      n = n + dir;
      if(n > 7)
      {
        dir = -1;
      }
      else if(n < 1)
      {
        dir = 1;
      }
    } else {
      Music.noteOff();
      noteIsOn = false;
    }
    lastTime = time;
  }

}

