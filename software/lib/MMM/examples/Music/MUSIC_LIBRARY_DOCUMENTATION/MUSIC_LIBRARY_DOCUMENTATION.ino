/////////////////////////////////////////////////////////////////////////
// DON'T TRY TO RUN THIS SKETCH, IT IS FOR DOCUMENTATION PURPOSES ONLY //
/////////////////////////////////////////////////////////////////////////

// These are the music functions that are available for you to use in you sketches.
// You can see examples of how some of them are used (the most basic ones) in the
// Apps folder that downloaded with the MM library.

// In the following you can see the variable type that the function takes as an argument (float, uint8_t or uint16_t)
// The weirdly looking "uint16_t" and "uint8_t" is just unsigned 16 and 8 bit integers. So instead of having
// both negative and positive values, they only have positive values from 0 - 255 (8bit) and 0 - 65535 (16bit).
// If you copy a function from here to your arduino sketch, just change the word "float", "uint8_t", etc into the
// variable name that you uses in your sketch.


// INITIALIZER
// Use this to start the synth engine. It defaults to a sine tone at 110Hz, no envelope and no detune.
Music.init();


// FREQUENCY AND DETUNE FUNCTIONS
// Use these functions to set the frequency and detune parameters of the synth.
Music.setFrequency(float);   // Set frequencies of all oscillators at once. Does _not_ affect detune.
Music.setFrequency1(float);  // Set frequency of individual oscillators.
Music.setFrequency2(float);  //
Music.setFrequency3(float);  //
Music.setDetune(float);      // Set the detune of all oscillators at once. Does _not_ affect the base frequencies.
Music.setDetune2(float);     // Set the detune of oscillator 2 and 3 individually (oscillator 1 stays fixed)
Music.setDetune3(float);
Music.pitchBend(float);      // This function detunes the pitch without affecting the detune parameters' individual
                             // 'spread'. Takes a float.


// WAVEFORM FUNCTIONS
// Switch between the different waveforms for the oscillators. It sets all of them at once.
Music.setSine();
Music.setSaw();
Music.setSquare();


// GAIN FUNCTIONS
// Set the gain of the oscillators all at once or individually. You can send either floats or uint16_t to the
// function and it figures out to use the correct function automagically :)
Music.setGain(float); // 0.0 - 1.0
Music.setGain1(float); // 0.0 - 1.0 
Music.setGain2(float); // 0.0 - 1.0
Music.setGain3(float); // 0.0 - 1.0
// using floats in your own calculations can be heavy on the processor, so there is the option of passing 16bit integers
// instead, since this is what it gets converted to anyway internally in the sound engine.
Music.setGain(uint16_t value); // 0 - 65535
Music.setGain1(uint16_t value); // 0 - 65535 
Music.setGain2(uint16_t value); // 0 - 65535
Music.setGain3(uint16_t value); // 0 - 65535


// NOTE FUNCTIONS
// These functions triggers a note to be played. The noteOff() functions turns the note off again.
// They come both with note and velocity information (for noteOn). If you don't know what that is,
// just use the ones with the least arguments.
// To get a proper note sound call Music.enableEnvelopes() [see below] before calling the noteOn function.
// You just have to do that once in the setup for example.
Music.noteOn(uint8_t note, uint8_t vel); // 0 - 127
Music.noteOn(uint8_t note); // 0 - 127
Music.noteOff(uint8_t note); // 0 - 127
Music.noteOff();
// This function returns the frequency of a MIDI note number sent to it.
Music.getNoteFrequency(uint8_t); // 0 - 127


// ENVELOPE FUNCTIONS
// These functions enables and sets the parameters of the internal envelope which creates dynamics for the notes 
// being played. You can read about ADSR envelopes here: http://en.wikipedia.org/wiki/Synthesizer#ADSR_envelope
// When using the envelope you can only hear sound when you are triggering the notes with the note functions. In order
// to get dynamics without triggering the note object you must have the envelope turned off, for example using 
// the Music.disableEnvelope() function [already set by default in the init() function]. You can then control the
// dynamics of the sound with the overall or individual setGain() functions.
Music.enableEnvelope();
Music.disableEnvelope();
// Setting the parameters for the envelope you send an 8bit number between 0 and 127 to the functions below. 0 is a very fast
// rise or decay in sound, whereas 127 is very long. Sustain is the sound level where 0 is silent and 127 is full gain. 
// You must experiment with what suits your musical taste :)
// These parameters can of course be adjusted during the physics code for interesting results, but be aware that when
// using the sine wave oscillator (which is more processor intensive) the sound can hang or have glitches if you alter
// these parameters too quickly or set them at extremes. Try it out.
Music.setAttack(uint8_t att); // 0 - 127
Music.setDecay(uint8_t dec); // 0 - 127
Music.setSustain(uint8_t sus); // 0 - 127
Music.setRelease(uint8_t rel); // 0 - 127
