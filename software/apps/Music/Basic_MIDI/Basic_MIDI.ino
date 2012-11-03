
// This needs to be in all sketches at the moment
#include <stdint.h>

// The Music and Midi objects are automatically instantiated when the header file is included.
// Make calls to the Music and Midi objects with "Music.function(args)" and "Midi.function(args)"
// You still need to call Music.init() and Midi.init() in the setup() function below.
#include <Music.h>
#include <Midi.h>

// variables for this sketch

void setup() {

  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();
  
  // We initialize the MIDI engine by calling Midi.init()
  Midi.init();
  
  // Choosing the sine wave oscillator (optional since this is already the default).
  Music.setSaw();
    
  // Detuning the three oscillators heavily to create more movement in the sound.
  Music.setDetune(0.01);  
  
  // Enabling envelope, otherwise the synth would just play constant tones.
  Music.enableEnvelope();

}

void loop() {
  
  // The MIDI must be used with the external 
  // "IAC2Serial.pde" Processing sketch.
  Midi.checkMidi();
    
}

