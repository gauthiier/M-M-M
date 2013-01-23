
// This needs to be in all sketches at the moment
#include <stdint.h>

// The Music and Midi objects are automatically instantiated when the header file is included.
// Make calls to the Music and Midi objects with "Music.function(args)" and "Midi.function(args)"
// You still need to call Music.init() and Midi.init() in the setup() function below.
#include <Music.h>

void setup() {
  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();

}

void loop() {

}

