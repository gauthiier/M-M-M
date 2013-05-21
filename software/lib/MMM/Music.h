/* 
 Music.h - Music library
 Copyright (c) 2012 Copenhagen Institute of Interaction Design. 
 All right reserved.
 
 This library is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser Public License for more details.
 
 You should have received a copy of the GNU Lesser Public License
 along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + author: Jakob Bak
 + contact: j.bak@ciid.dk
 */


#ifndef Music_h // include guard
#define Music_h

//#include <avr/io.h>  // see if needed
#include "Arduino.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h> 
#include <hardwareSerial.h>
#include "Wavetable.h"




// current sample rate is 15625 as defined in the init() section
#define SAMPLE_RATE 15625

// Defining which pins the SPI interface is connected to.
#define SPI_SCK 5
#define SPI_MOSI 3

// Checking if NUM_OSCILLATORS is set, and if not, default to 1 oscillator
#ifndef NUM_OSCILLATORS
	#define NUM_OSCILLATORS 1
#elif (NUM_OSCILLATORS == 1)||(NUM_OSCILLATORS == 2)||(NUM_OSCILLATORS == 3)
#else
	#error NUM_OSCILLATORS shall be 1, 2 or 3
#endif

// Checking if BIT_DEPTH is set, and if not, default to 8bit
#ifndef BIT_DEPTH
	#define BIT_DEPTH 8
#elif (BIT_DEPTH == 8)||(BIT_DEPTH == 12)
#else
	#error BIT_DEPTH shall be 8 or 12
#endif


// Shortnames for waveforms
#define SINE 0
#define	SQUARE 1
#define PULSE 2
#define TRIANGLE 3
#define SAW 4
#define FUZZ 5
#define DIGI1 6
#define DIGI2 7
#define DIGI3 8
#define DIGI4 9
#define NOISE 10
#define DIGI6 11
#define TAN1 12
#define TAN2 13
#define TAN3 14
#define TAN4 15

// Maximum possible value for amplification envelope in audio code
#define MAX_ENV_GAIN 65535




// MIDI specific constants
#ifndef MIDI_CHANNEL
	#define MIDI_CHANNEL 1
#elif (MIDI_CHANNEL > 0)&&(MIDI_CHANNEL < 17)
#else
	#error MIDI_CHANNEL should be between 1 - 16
#endif

//synth parameters as MIDI controller numbers
#define DETUNE 4
#define WAVEFORM 5
#define PORTAMENTO 6	// not implemented yet

#define FREQUENCY1 10
#define SEMITONE1 11
#define DETUNE1 12
#define GAIN1 13
#define WAVEFORM1 14
#define FM1 15

#define FREQUENCY2 20
#define SEMITONE2 21
#define DETUNE2 22
#define GAIN2 23
#define WAVEFORM2 24
#define FM2 25

#define FREQUENCY3 30
#define SEMITONE3 31
#define DETUNE3 32
#define GAIN3 33
#define WAVEFORM3 34
#define FM3 35

#define ENV_ATTACK 114
#define ENV_DECAY 115
#define ENV_SUSTAIN 116
#define ENV_RELEASE 117



// Table of MIDI note values to frequency in Hertz
prog_uint16_t hertzTable[] PROGMEM = {8,8,9,9,10,10,11,12,12,13,14,15,16,17,18,19,20,21,23,24,25,27,29,30,32,34,36,38,41,43,46,48,51,54,58,61,65,69,73,77,82,87,92,97,103,109,116,123,130,138,146,155,164,174,184,195,207,219,233,246,261,277,293,311,329,349,369,391,415,440,466,493,523,554,587,622,659,698,739,783,830,880,932,987,1046,1108,1174,1244,1318,1396,1479,1567,1661,1760,1864,1975,2093,2217,2349,2489,2637,2793,2959,3135,3322,3520,3729,3951,4186,4434,4698,4978,5274,5587,5919,6271,6644,7040,7458,7902,8372,8869,9397,9956,10548,11175,11839,12543};

// Used in the functions that set the envelope timing
prog_uint32_t envTimeTable[] PROGMEM = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,73,75,77,79,81,83,85,87,89,92,95,98,101,104,108,112,116,120,124,128,132,136,140,145,150,155,160,165,170,176,182,188,194,201,208,215,222,230,238,247,257,268,280,293,307,322,341,379,425,482,556,654,792,998,1342,2030,4095};

float semitoneTable[] = {0.25,0.2648658,0.2806155,0.29730177,0.31498027,0.33370996,0.35355338,0.37457678,0.39685026,0.4204482,0.44544938,0.47193715,0.5,0.5297315,0.561231,0.59460354,0.62996054,0.6674199,0.70710677,0.74915355,0.7937005,0.8408964,0.8908987,0.9438743,1.0,1.0594631,1.122462,1.1892071,1.2599211,1.3348398,1.4142135,1.4983071,1.587401,1.6817929,1.7817974,1.8877486,2.0,2.1189263,2.244924,2.3784142,2.5198421,2.6696796,2.828427,2.9966142,3.174802,3.3635857,3.563595,3.7754972,4.0};




// MMusic class for handling sound engine

class MMusic {    
public:
	
	// INITIALIZER
    void init();

	// AUDIO INTERRUPT SERVICE ROUTINE
	void synthInterrupt8bit();
	void synthInterrupt8bitFM();
	void synthInterrupt12bitSine();
	void synthInterrupt12bitSineFM();
		
	// FREQUENCY AND DETUNE FUNCTIONS
	void setFrequency(float frequency);
	void setFrequency1(float frequency1);
	void setFrequency2(float frequency2);
	void setFrequency3(float frequency3);
	void setSemitone1(int8_t semi);
	void setSemitone2(int8_t semi);
	void setSemitone3(int8_t semi);
	void setDetune(float detune);
	void setDetune1(float detune);
	void setDetune2(float detune);
	void setDetune3(float detune);
	void setFM1(uint8_t fm);
	void setFM2(uint8_t fm);
	void setFM3(uint8_t fm);
	void pitchBend(float b); // NOT IMPLEMENTED
	
	// WAVEFORM FUNCTIONS
	void setWaveform(uint16_t waveForm);    // JUST FOR 8bit WAVEFORMS
	void setWaveform1(uint16_t waveForm);   //
	void setWaveform2(uint16_t waveForm);   //
	void setWaveform3(uint16_t waveForm);   //
	
	// GAIN FUNCTIONS
	void setGain(float value); // 0.0 - 1.0          
	void setGain1(float value); // 0.0 - 1.0         
	void setGain2(float value); // 0.0 - 1.0         
	void setGain3(float value); // 0.0 - 1.0         
	float getGain();       // 0.0 - 1.0         
	float getGain1();       // 0.0 - 1.0         
	float getGain2();       // 0.0 - 1.0         
	float getGain3();       // 0.0 - 1.0         

	// NOTE FUNCTIONS
	void noteOn(uint8_t note, uint8_t vel); // 0 - 127
	void noteOn(uint8_t note); // 0 - 127
	void noteOff(uint8_t note); // 0 - 127
	void noteOff();
	uint16_t getNoteFrequency(uint8_t note); // 0 - 127
	
	// ENVELOPE FUNCTIONS
	void enableEnvelope();
	void disableEnvelope();
	void setEnvStage(uint8_t stage); // 0 - 4
	
	void setAttack(uint8_t att); // 0 - 127              
	void setDecay(uint8_t dec); // 0 - 127               
	void setSustain(uint8_t sus); // 0 - 127             
	void setRelease(uint8_t rel); // 0 - 127             
	
	void setVelSustain(uint8_t vel); // 0 - 127
	void setVelPeak(uint8_t vel); // 0 - 127

	
	
private:
	
	// WAVEFORM VARIABLES
	uint16_t waveForm1;
	uint16_t waveForm2;
	uint16_t waveForm3;
	uint16_t waveForm;
	bool sine;
	bool saw;
	bool square;
	
	// FREQUENCY VARIABLES
	uint16_t period1;
	uint16_t period2;
	uint16_t period3;
	uint16_t frequency16bit;
	float frequency;
	float frequency1;
	float frequency2;
	float frequency3;
	float semi1;
	float semi2;
	float semi3;
	float detune1;
	float detune2;
	float detune3;
	float bend;
	
	// OSCILLATOR VARIABLES
	uint16_t accumulator1;
	uint16_t accumulator2;
	uint16_t accumulator3;
	uint16_t index1;
	uint16_t index2;
	uint16_t index3;
	uint32_t oscil1;
	uint32_t oscil2;
	uint32_t oscil3;
	int32_t modulator1;  // NOT USED
	int32_t modulator2;
	int32_t modulator3;  // NOT USED
	int8_t fmAmount1;  // NOT USED
	int8_t fmAmount2;
	int8_t fmAmount3;  // NOT USED
	uint16_t gain;
	uint16_t gain1;
	uint16_t gain2;
	uint16_t gain3;
	
	// ENVELOPE VARIABLES
	bool envelopeOn;
	uint32_t env;
	uint8_t envStage;
	
	uint16_t attack;
	uint16_t decay;
	uint16_t sustain;
	uint16_t release;
	uint16_t velSustain;
	uint16_t velPeak;
	
	// NOTE VARIABLE
	uint8_t notePlayed;
	
	// final sample that goes to the DAC    
	uint32_t sample;
	
	// the two bytes that go to the DAC over SPI
	uint8_t dacSPI0;
	uint8_t dacSPI1;
    
};

extern MMusic Music;




#ifdef MIDI

// MMidi class for handling MIDI implementation

class MMidi {
public:
	void init();
	void checkMidi();
	
	void midiHandler();
	void noteOff(uint8_t channel, uint8_t note, uint8_t vel);
	void noteOn(uint8_t channel, uint8_t note, uint8_t vel);
	void aftertouch(uint8_t channel, uint8_t note, uint8_t pressure);
	void controller(uint8_t channel, uint8_t number, uint8_t value);
	void programChange(uint8_t channel, uint8_t number);
	void channelPressure(uint8_t channel, uint8_t pressure);
	void pitchWheel(uint8_t channel, uint8_t highBits, uint8_t lowBits);
	
private:
	
	// MIDI
	uint8_t data;
	uint8_t midiBuffer[3];
	uint8_t midiChannel;
	
	int midiBufferIndex;
	uint16_t frequency;
	uint8_t notePlayed;
};

extern MMidi Midi;

#endif



//////////////////////////////////////////////////////////
//
// AUDIO INTERRUPT - The pre-processor selects 8 or 12 bit
//
//////////////////////////////////////////////////////////
ISR(TIMER2_COMPA_vect) { // timer 2 is audio interrupt timer
	
	OCR2A = 127; // don't change this
	
#if	BIT_DEPTH == 8
	#ifdef FM	
		Music.synthInterrupt8bitFM();
	#else
		Music.synthInterrupt8bit();
	#endif
#endif
#if BIT_DEPTH == 12
	#ifdef FM	
		Music.synthInterrupt12bitSineFM();
	#else
		Music.synthInterrupt12bitSine();
	#endif
#endif
	
}





/////////////////////////////////////////////////////////
//
//	8 BIT WAVETABLE - AUDIO INTERRUPT SERVICE ROUTINE
//
/////////////////////////////////////////////////////////


void inline MMusic::synthInterrupt8bit()
{
	
	PORTD &= ~(1<<3);
	
	// Frame sync low for SPI (making it low here so that we can measure lenght of interrupt with scope)
#ifdef CFO
	PORTB &= ~(1<<2);
#else
	PORTD &= ~(1<<6);
#endif
	
	accumulator1 = accumulator1 + period1;
	index1 = accumulator1 >> 8;
	//oscil1 = 0;
	memcpy_P(&oscil1, &waveTable[index1 + waveForm1],1);
	sample = (oscil1 * gain1);
	
#if (NUM_OSCILLATORS==2) || (NUM_OSCILLATORS==3)
	
	accumulator2 = accumulator2 + period2;
	index2 = accumulator2 >> 8;
	//oscil2 = 0;
	memcpy_P(&oscil2, &waveTable[index2 + waveForm2],1);
	sample += (oscil2 * gain2);
	
#endif	
#if NUM_OSCILLATORS==3
	
	accumulator3 = accumulator3 + period3;
	index3 = accumulator3 >> 8;
	//oscil3 = 0;
	memcpy_P(&oscil3, &waveTable[index3 + waveForm3],1);
	sample += (oscil3 * gain3); 
	
#endif
	
	sample >>= 10;
	
	
	// AMPLIFICATION ENVELOPE
	// Amplification envelope is calculated here
	if(envelopeOn) {
		
		// Attack
		if(envStage == 1) {
			env += attack;
			if(velPeak < env) {
				env = velPeak;
				envStage = 2;
			}
		}
		// Decay
		else if(envStage == 2) {
			env -= decay;
			if(env < velSustain || MAX_ENV_GAIN < env) {
				env = velSustain;
				envStage = 3;
			}
		}
		// Sustain
		else if (envStage == 3) {
			env = velSustain;
		}
		
		// Release
		else if (envStage == 4) {
			env -= release;
			if(MAX_ENV_GAIN < env) {
				env = 0;
				envStage = 0;
			}
		}
		/*		 
		 // No gain
		 else if (envStage == 0) {
		 env = 0;
		 //accumulator1 = 0;
		 //accumulator2 = 0;
		 //accumulator3 = 0;
		 }
		 */		 
	} else {
		env = 65535;
	}
	
	// Adding the amplification envelope (16bit) we bring it back to the 16bit frame again afterwards.
	sample = (env * sample) >> 16;
	
	
	// Formatting the samples to be transfered to the MCP4921 DAC  
	dacSPI0 = sample >> 8;
	dacSPI0 >>= 4;
	dacSPI0 |= 0x30;
	dacSPI1 = sample >> 4;
	
	SPCR |= (1 << MSTR);
	
	// transmit value out the SPI port
	SPDR = dacSPI0;
	while (!(SPSR & (1<<SPIF)));  // Maybe this can be optimised
	SPDR = dacSPI1;
	while (!(SPSR & (1<<SPIF)));  // Maybe this can be optimised
	
	// Frame sync high
#ifdef CFO
	PORTB |= (1<<2);
#else
	PORTD |= (1<<6);
#endif
}




/////////////////////////////////////////////////////////
//
//	8 BIT WAVETABLE - AUDIO INTERRUPT SERVICE ROUTINE
//
/////////////////////////////////////////////////////////


void inline MMusic::synthInterrupt8bitFM ()
{
	
	PORTD &= ~(1<<3);
	
	// Frame sync low for SPI (making it low here so that we can measure lenght of interrupt with scope)
#ifdef CFO
	PORTB &= ~(1<<2);
#else
	PORTD &= ~(1<<6);
#endif
	
	accumulator1 = accumulator1 + period1;
	index1 = accumulator1 >> 8;
	//oscil1 = 0;
	memcpy_P(&oscil1, &waveTable[index1 + waveForm1],1);
	//sample = (oscil1 * gain1);
	
	//modulator2 = 0;
	modulator2 = (fmAmount2 * (oscil1-128) * int32_t(period2))>>14;
	//modulator2 = (period2 * (oscil1-128))>>7;
	accumulator2 = accumulator2 + period2 + modulator2;
	index2 = accumulator2 >> 8;
	//oscil2 = 0;
	memcpy_P(&oscil2, &waveTable[index2 + waveForm2],1);
	sample = (oscil2 * gain2);

	sample >>= 8;
	
	
	// AMPLIFICATION ENVELOPE
	// Amplification envelope is calculated here
	if(envelopeOn) {
		
		// Attack
		if(envStage == 1) {
			env += attack;
			if(velPeak < env) {
				env = velPeak;
				envStage = 2;
			}
		}
		// Decay
		else if(envStage == 2) {
			env -= decay;
			if(env < velSustain || MAX_ENV_GAIN < env) {
				env = velSustain;
				envStage = 3;
			}
		}
		// Sustain
		else if (envStage == 3) {
			env = velSustain;
		}
		
		// Release
		else if (envStage == 4) {
			env -= release;
			if(MAX_ENV_GAIN < env) {
				env = 0;
				envStage = 0;
			}
		}
		/*		 
		 // No gain
		 else if (envStage == 0) {
		 env = 0;
		 //accumulator1 = 0;
		 //accumulator2 = 0;
		 //accumulator3 = 0;
		 }
		 */		 
	} else {
		env = 65535;
	}
	
	// Adding the amplification envelope (16bit) we bring it back to the 16bit frame again afterwards.
	sample = (env * sample) >> 16;
	
	
	// Formatting the samples to be transfered to the MCP4921 DAC  
	dacSPI0 = sample >> 8;
	dacSPI0 >>= 4;
	dacSPI0 |= 0x30;
	dacSPI1 = sample >> 4;
	
	SPCR |= (1 << MSTR);
	
	// transmit value out the SPI port
	SPDR = dacSPI0;
	while (!(SPSR & (1<<SPIF)));  // Maybe this can be optimised
	SPDR = dacSPI1;
	while (!(SPSR & (1<<SPIF)));  // Maybe this can be optimised
	
	// Frame sync high
#ifdef CFO
	PORTB |= (1<<2);
#else
	PORTD |= (1<<6);
#endif
}




/////////////////////////////////////////////////////////
//
//	12 BIT SINEWAVE - AUDIO INTERRUPT SERVICE ROUTINE
//
/////////////////////////////////////////////////////////


void MMusic::synthInterrupt12bitSine()
{
	// Frame sync low for SPI (making it low here so that we can measure lenght of interrupt with scope)
#ifdef CFO
	PORTB &= ~(1<<2);
#else
	PORTD &= ~(1<<6);
#endif
	
	accumulator1 = accumulator1 + period1;
	index1 = accumulator1 >> 4;
	memcpy_P(&oscil1, &sineTable[index1],2);
	sample = (oscil1 * gain1) << 2; 
	
#if (NUM_OSCILLATORS==2) || (NUM_OSCILLATORS==3)
	
	accumulator2 = accumulator2 + period2;
	index2 = accumulator2 >> 4;
	memcpy_P(&oscil2, &sineTable[index2],2);
	sample += (oscil2 * gain2) << 2; 
	
#endif	
#if NUM_OSCILLATORS==3
	
	accumulator3 = accumulator3 + period3;	
	index3 = accumulator3 >> 4;	
	memcpy_P(&oscil3, &sineTable[index3],2);
	sample += (oscil3 * gain3) << 2; 
	
#endif
	
	sample >>= 16;
	
	
	// AMPLIFICATION ENVELOPE
	// Amplification envelope is calculated here
	if(envelopeOn) {
		
		// Attack
		if(envStage == 1) {
			env += attack;
			if(velPeak < env) {
				env = velPeak;
				envStage = 2;
			}
		}
		// Decay
		else if(envStage == 2) {
			env -= decay;
			if(env < velSustain || MAX_ENV_GAIN < env) {
				env = velSustain;
				envStage = 3;
			}
		}
		// Sustain
		else if (envStage == 3) {
			env = velSustain;
		}
		
		// Release
		else if (envStage == 4) {
			env -= release;
			if(MAX_ENV_GAIN < env) {
				env = 0;
				envStage = 0;
			}
		}
		/*		 
		 // No gain
		 else if (envStage == 0) {
		 env = 0;
		 //accumulator1 = 0;
		 //accumulator2 = 0;
		 //accumulator3 = 0;
		 }
		 */		 
	} else {
		env = 65535;
	}
	
	// Adding the amplification envelope (16bit) we bring it back to the 16bit frame again afterwards.
	sample = (env * sample) >> 16;
 	
	// Formatting the samples to be transfered to the MCP4921 DAC  
	dacSPI0 = sample >> 8;
	dacSPI0 >>= 4;
	dacSPI0 |= 0x30;
	dacSPI1 = sample >> 4;
	
	SPCR |= (1 << MSTR);
	
	// transmit value out the SPI port
	SPDR = dacSPI0;
	while (!(SPSR & (1<<SPIF)));  // Maybe this can be optimised
	SPDR = dacSPI1;
	while (!(SPSR & (1<<SPIF)));  // Maybe this can be optimised
	
	// Frame sync high
#ifdef CFO
	PORTB |= (1<<2);
#else
	PORTD |= (1<<6);
#endif
	// Frame sync high
	PORTD |= (1<<3);
	
}




/////////////////////////////////////////////////////////
//
//	12 BIT SINEWAVE - AUDIO INTERRUPT SERVICE ROUTINE
//
/////////////////////////////////////////////////////////


void MMusic::synthInterrupt12bitSineFM()
{
	// Frame sync low for SPI (making it low here so that we can measure lenght of interrupt with scope)
#ifdef CFO
	PORTB &= ~(1<<2);
#else
	PORTD &= ~(1<<6);
#endif
	
	accumulator1 = accumulator1 + period1;
	index1 = accumulator1 >> 4;
	memcpy_P(&oscil1, &sineTable[index1],2);
	//sample = (oscil1 * gain1) << 2; 
	
	//modulator2 = 0;
	modulator2 = (fmAmount2 * int32_t(oscil1-2048))>>2;
	modulator2 = (modulator2 * int32_t(period2))>>16;
	accumulator2 = accumulator2 + period2 + modulator2;
	//accumulator2 = accumulator2 + period2;
	index2 = accumulator2 >> 4;
	memcpy_P(&oscil2, &sineTable[index2],2);
	sample = (oscil2 * gain2); 
	sample >>= 12;
	
	
	// AMPLIFICATION ENVELOPE
	// Amplification envelope is calculated here
	if(envelopeOn) {
		
		// Attack
		if(envStage == 1) {
			env += attack;
			if(velPeak < env) {
				env = velPeak;
				envStage = 2;
			}
		}
		// Decay
		else if(envStage == 2) {
			env -= decay;
			if(env < velSustain || MAX_ENV_GAIN < env) {
				env = velSustain;
				envStage = 3;
			}
		}
		// Sustain
		else if (envStage == 3) {
			env = velSustain;
		}
		
		// Release
		else if (envStage == 4) {
			env -= release;
			if(MAX_ENV_GAIN < env) {
				env = 0;
				envStage = 0;
			}
		}
		/*		 
		 // No gain
		 else if (envStage == 0) {
		 env = 0;
		 //accumulator1 = 0;
		 //accumulator2 = 0;
		 //accumulator3 = 0;
		 }
		 */		 
	} else {
		env = 65535;
	}
	
	// Adding the amplification envelope (16bit) we bring it back to the 16bit frame again afterwards.
	sample = (env * sample) >> 16;
 	
	// Formatting the samples to be transfered to the MCP4921 DAC  
	dacSPI0 = sample >> 8;
	dacSPI0 >>= 4;
	dacSPI0 |= 0x30;
	dacSPI1 = sample >> 4;
	
	SPCR |= (1 << MSTR);
	
	// transmit value out the SPI port
	SPDR = dacSPI0;
	while (!(SPSR & (1<<SPIF)));  // Maybe this can be optimised
	SPDR = dacSPI1;
	while (!(SPSR & (1<<SPIF)));  // Maybe this can be optimised
	
	// Frame sync high
#ifdef CFO
	PORTB |= (1<<2);
#else
	PORTD |= (1<<6);
#endif
	// Frame sync high
	PORTD |= (1<<3);
	
}




MMusic Music;

#ifdef MIDI
MMidi Midi;
#endif




/////////////////////////////////////
//
//	INITIALIZING FUNCTION
//
/////////////////////////////////////

void MMusic::init()
{
	// clear interrupts. to make sure the interrupt timer doesn't start until we've set it up.
	//cli();
	
	// set up syntheziser
	// this is the timer 2 audio rate timer, fires an interrupt at 15625 Hz sampling rate
	TIMSK2 = 1<<OCIE2A;                      // interrupt enable audio timer
	OCR2A = 127;
	TCCR2A = 2;                              // CTC mode, counts up to 127 then resets
	TCCR2B = 0<<CS22 | 1<<CS21 | 0<<CS20;
	
	// OUTPUTS
	// sck + mosi + ss
	DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB5);
	// dac_cs output
#ifdef CFO
	DDRB |= (1 << DDB2) | (1 << DDB3);
#else
	DDRD |= (1 << DDD6) | (1 << DDB3);
#endif
	
	// set up SPI port
	SPCR = 0x50;
	SPSR = 0x01;
	
	// DAC frame sync HIGH, so that the SPI port doesn't start wirting straight away
#ifdef CFO
	PORTB |= (1<<2);
#else
	PORTD |= (1<<6);
#endif
	
	// waveform setup
	//setSine();
	setWaveform(0);
	
	// frequency setup
	setFrequency(440);
	setSemitone1(0);
	setSemitone2(0);
	setSemitone3(0);
	setDetune(0);
	
	// gain setup
	setGain(1.0f);
	setGain1(1.0f);
	setGain2(1.0f);
	setGain3(1.0f);
	
	// envelope setup
	setEnvStage(0);
	disableEnvelope();
	env = 0;
	
	setAttack(4);
	setDecay(90);
	setSustain(32);
	setRelease(64);
	setVelSustain(0);
	
	setFM2(0);
	
	//sei(); // global interrupt enable 
	
	//Serial.println("MUSIC INITIALIZED!");
}




/////////////////////////////////////
//
//	FREQUENCY AND DETUNE FUNCTIONS
//
/////////////////////////////////////

void MMusic::setFrequency(float freq)
{
	period1 = uint16_t(((freq * semi1 * (1 + detune1 + bend)) * 65536.0) / SAMPLE_RATE);
	period2 = uint16_t(((freq * semi2 * (1 + detune2 + bend)) * 65536.0) / SAMPLE_RATE);
	period3 = uint16_t(((freq * semi3 * (1 + detune3 + bend)) * 65536.0) / SAMPLE_RATE);
	frequency = freq;
	frequency1 = freq;
	frequency2 = freq;
	frequency3 = freq;
}


void MMusic::setFrequency1(float freq)
{
	frequency1 = freq;
	period1 = uint16_t(((frequency1 * semi1 * (1 + detune1 + bend)) * 65536.0) / SAMPLE_RATE);
}


void MMusic::setFrequency2(float freq)
{
	frequency2 = freq;
	period2 = uint16_t(((frequency2 * semi2 * (1 + detune2 + bend)) * 65536.0) / SAMPLE_RATE);
}


void MMusic::setFrequency3(float freq)
{
	frequency3 = freq;
	period3 = uint16_t(((frequency3 * semi3 * (1 + detune3 + bend)) * 65536.0) / SAMPLE_RATE);
}


void MMusic::setSemitone1(int8_t semi)
{
	if(-25 < semi && semi < 25){
		semi1 = semitoneTable[semi+24];
	} else if (semi < -24) {
		semi1 = semitoneTable[0];
	} else {
		semi1 = semitoneTable[48];
	}
	period1 = uint16_t(((frequency1 * semi1 * (1 + detune1 + bend)) * 65536.0) / SAMPLE_RATE);
}


void MMusic::setSemitone2(int8_t semi)
{
	if(-25 < semi && semi < 25){
		semi2 = semitoneTable[semi+24];
	} else if (semi < -24) {
		semi2 = semitoneTable[0];
	} else {
		semi2 = semitoneTable[48];
	}
	period2 = uint16_t(((frequency2 * semi2 * (1 + detune2 + bend)) * 65536.0) / SAMPLE_RATE);
}


void MMusic::setSemitone3(int8_t semi)
{
	if(-25 < semi && semi < 25){
		semi3 = semitoneTable[semi+24];
	} else if (semi < -24) {
		semi3 = semitoneTable[0];
	} else {
		semi3 = semitoneTable[48];
	}
	period3 = uint16_t(((frequency3 * semi3 * (1 + detune3 + bend)) * 65536.0) / SAMPLE_RATE);
}


void MMusic::setDetune(float detune)
{
	detune1 = 0.0;
	detune2 = detune;
	detune3 = -detune;
	period2 = uint16_t(((frequency2 * semi2 * (1 + detune2 + bend)) * 65536.0) / SAMPLE_RATE);
	period3 = uint16_t(((frequency3 * semi3 * (1 + detune3 + bend)) * 65536.0) / SAMPLE_RATE);
}


void MMusic::setDetune1(float detune)
{
	detune1 = detune;
	period1 = uint16_t(((frequency1 * semi1 * (1 + detune1 + bend)) * 65536.0) / SAMPLE_RATE);
}


void MMusic::setDetune2(float detune)
{
	detune2 = detune;
	period2 = uint16_t(((frequency2 * semi2 * (1 + detune2 + bend)) * 65536.0) / SAMPLE_RATE);
}


void MMusic::setDetune3(float detune)
{
	detune3 = detune;
	period3 = uint16_t(((frequency3 * semi3 * (1 + detune3 + bend)) * 65536.0) / SAMPLE_RATE);
}


void MMusic::pitchBend(float b)
{
	bend = b;
	period1 = uint16_t(((frequency1 * semi1 * (1 + detune1 + bend)) * 65536.0) / SAMPLE_RATE);
	period2 = uint16_t(((frequency2 * semi2 * (1 + detune2 + bend)) * 65536.0) / SAMPLE_RATE);
	period3 = uint16_t(((frequency3 * semi3 * (1 + detune3 + bend)) * 65536.0) / SAMPLE_RATE);	
}


void MMusic::setFM1(uint8_t fm) {
	fmAmount1 = fm;
}


void MMusic::setFM2(uint8_t fm) {
	fmAmount2 = fm;
}


void MMusic::setFM3(uint8_t fm) {
	fmAmount3 = fm;
}




/////////////////////////////////////
//
//	WAVEFORM FUNCTIONS
//
/////////////////////////////////////


void MMusic::setWaveform(uint16_t waveForm)
{
	waveForm1 = waveForm * 256;
	waveForm2 = waveForm * 256;
	waveForm3 = waveForm * 256;
}


void MMusic::setWaveform1(uint16_t waveForm)
{
	waveForm1 = waveForm * 256;
}


void MMusic::setWaveform2(uint16_t waveForm)
{
	waveForm2 = waveForm * 256;
}


void MMusic::setWaveform3(uint16_t waveForm)
{
	waveForm3 = waveForm * 256;
}




/////////////////////////////////////
//
//	GAIN FUNCTIONS
//
/////////////////////////////////////


void MMusic::setGain(float value)
{
	gain = uint16_t(value * 65535);
	gain1 = gain;
	gain2 = gain;
	gain3 = gain;
}


void MMusic::setGain1(float value)
{
	gain1 = uint16_t(value * 65535);
}


void MMusic::setGain2(float value)
{
	gain2 = uint16_t(value * 65535);
}


void MMusic::setGain3(float value)
{
	gain3 = uint16_t(value * 65535);
}


float MMusic::getGain()
{
	return float(gain)/65535.0;
}


float MMusic::getGain1()
{
	return float(gain1)/65535.0;
}


float MMusic::getGain2()
{
	return float(gain2)/65535.0;
}


float MMusic::getGain3()
{
	return float(gain3)/65535.0;
}




/////////////////////////////////////
//
//	NOTE_ON/OFF FUNCTIONS
//
/////////////////////////////////////


void MMusic::noteOn(uint8_t note, uint8_t vel)
{	
	envStage = 1;
	setVelSustain(vel);
	setVelPeak(vel);
	notePlayed = note;
	memcpy_P(&frequency16bit, &hertzTable[notePlayed],2);
	setFrequency1(frequency16bit);
	setFrequency2(frequency16bit);
	setFrequency3(frequency16bit);
}


void MMusic::noteOn(uint8_t note)
{	
	envStage = 1;
	setVelSustain(127);
	setVelPeak(127);
	notePlayed = note;
	memcpy_P(&frequency16bit, &hertzTable[notePlayed],2);
	setFrequency1(frequency16bit);
	setFrequency2(frequency16bit);
	setFrequency3(frequency16bit);
}


void MMusic::noteOff(uint8_t note)
{	
	if(notePlayed == note) {
		envStage = 4;
	}    
}


void MMusic::noteOff()
{	
	envStage = 4;
}



uint16_t MMusic::getNoteFrequency(uint8_t note)
{
	int f;
	memcpy_P(&f, &hertzTable[note], 2);
	return f;
}


/////////////////////////////////////
//
//	ENVELOPE FUNCTIONS
//
/////////////////////////////////////

void MMusic::enableEnvelope()
{
	envelopeOn = true;
}


void MMusic::disableEnvelope()
{
	envelopeOn = false;
}


void MMusic::setEnvStage(uint8_t stage)
{
	envStage = stage;
}


void MMusic::setAttack(uint8_t att)
{
	if(att>127) att = 127;
	memcpy_P(&attack, &envTimeTable[127 - att],2);
}


void MMusic::setDecay(uint8_t dec)
{
	if(dec>127) dec = 127;
	memcpy_P(&decay, &envTimeTable[127 - dec],2);
}


void MMusic::setSustain(uint8_t sus)
{
	sustain = ((sus * MAX_ENV_GAIN)/128);	
}


void MMusic::setRelease(uint8_t rel)
{
	if(rel>127) rel = 127;
	memcpy_P(&release, &envTimeTable[127 - rel],2);
}


void MMusic::setVelSustain(uint8_t vel)
{
	velSustain = vel * (sustain / 128);	
}


void MMusic::setVelPeak(uint8_t vel)
{
	velPeak = vel * (MAX_ENV_GAIN / 128);	
}




#ifdef MIDI

/////////////////////////////////////
//
//	MIDI specific functions
//
/////////////////////////////////////

bool midiRead = false;

void MMidi::init()
{	
	Serial.begin(9600);
	
	midiBufferIndex = 0;
	midiChannel = MIDI_CHANNEL - 1;
	if(midiChannel < 0 || midiChannel > 15) midiChannel = 0;
	
}

void MMidi::checkMidi()
{
	while(Serial.available() > 0) {
		
		data = Serial.read();
		
		if(data & 0x80 && (data & 0x0F) == midiChannel) {	// bitmask with 10000000 to see if byte is over 127 (data&0x80)
			midiBufferIndex = 0;							// and check if the midi channel corresponds to the midiChannel
			midiRead = true;								// the device is set to listen to.
		} else if(data & 0x80) {							// Else if the byte is over 127 (but not on the device's
			midiRead = false;								// midiChannel, don't read this or any following bytes.
		}
		
		if(midiRead) {
			midiBuffer[midiBufferIndex] = data;
			midiBufferIndex++;
			if (midiBufferIndex > 2) {
				midiHandler();
			}
		}
	}	
}


void MMidi::midiHandler() {
	
    uint8_t midiChannel = (midiBuffer[0] & 0x0F);
    
	
	switch(midiBuffer[0] & 0xF0) { // bit mask with &0xF0 ?
        case 0x80:
			noteOff			(midiBuffer[0] & 0x0F,     // midi channel 0-16
							 midiBuffer[1] & 0x7F,   // note value 0-127
							 midiBuffer[2] & 0x7F);  // note velocity 0-127
			break;
			
        case 0x90:
			noteOn			(midiBuffer[0] & 0x0F,     // midi channel 0-16
							 midiBuffer[1] & 0x7F,   // note value 0-127
							 midiBuffer[2] & 0x7F);  // note velocity 0-127
			break;
			
        case 0xA0:
			aftertouch		(midiBuffer[0] & 0x0F,   // midi channel 0-16
							 midiBuffer[1] & 0x7F, // note value 0-127
							 midiBuffer[2] & 0x7F);// note velocity 0-127
			break;
			
        case 0xB0:
			controller		(midiBuffer[0] & 0x0F,   // midi channel 0-16
							 midiBuffer[1] & 0x7F, // controller number 0-127
							 midiBuffer[2] & 0x7F);// controller value 0-127
			break;
			
        case 0xC0:
			programChange	(midiBuffer[0]  & 0x0F,    // midi channel 0-16
							 midiBuffer[1] & 0x7F);  // program number 0-127
			break;
			
        case 0xD0:
			channelPressure	(midiBuffer[0]  & 0x0F,    // midi channel 0-16
							 midiBuffer[1] & 0x7F);  // pressure amount 0-127
			break;
			
        case 0xE0:
			pitchWheel		(midiBuffer[0] & 0x0F,   // midi channel 0-16
							 midiBuffer[1] & 0x7F, // higher bits 0-6
							 midiBuffer[2] & 0x7F);// lower bits 7-13
			break;
			
        default:
			break;
	}
}


void MMidi::noteOff(uint8_t channel, uint8_t note, uint8_t vel) {
	
	if(notePlayed == note) {
		Music.setEnvStage(4);
	}
}


void MMidi::noteOn(uint8_t channel, uint8_t note, uint8_t vel) {
	
	Music.setEnvStage(1);
	Music.setVelSustain(vel);
	Music.setVelPeak(vel);
	notePlayed = note;
	memcpy_P(&frequency, &hertzTable[notePlayed],2);
	Music.setFrequency1(frequency);
	Music.setFrequency2(frequency);
	Music.setFrequency3(frequency);	
}


void MMidi::aftertouch(uint8_t channel, uint8_t note, uint8_t pressure) {
	// Write code here for Aftertouch 
}


void MMidi::controller(uint8_t channel, uint8_t number, uint8_t value) {
/*	Serial.println();
	Serial.print(channel);
	Serial.print('-');
	Serial.print(number);
	Serial.print('-');
	Serial.println(value);
*/	
	switch(number) {
		case DETUNE:
			Music.setDetune(value/5120.0);
			break;
		case PORTAMENTO:
			//Music.setPortamento(value);  // function to be defined, also argument
			break;
		case FREQUENCY1:
			Music.setFrequency1(Music.getNoteFrequency(value));
			break;
		case FREQUENCY2:
			Music.setFrequency2(Music.getNoteFrequency(value));
			break;
		case FREQUENCY3:
			Music.setFrequency3(Music.getNoteFrequency(value));
			break;
		case DETUNE1:
			Music.setDetune1(map(value,0,127,-100,100)*0.0005946);
			break;
		case DETUNE2:
			Music.setDetune2(map(value,0,127,-100,100)*0.0005946);
			//Music.setDetune2((value-64.0)*0.0005946);
			//Music.setDetune2(value/5120.0);
			break;
		case DETUNE3:
			Music.setDetune3(map(value,0,127,-100,100)*0.0005946);							 
			//Music.setDetune3((value-64.0)*0.0005946);
			//Music.setDetune3(value/5120.0);
			break;
		case SEMITONE1:
			if(15 < value && value < 113) {
				int8_t val = (((value-16)/2)-24);
				Music.setSemitone1(val);
			} else if (value < 16) {
				Music.setSemitone1(-24);				
			} else {
				Music.setSemitone1(24);
			}
			break;
		case SEMITONE2:
			if(15 < value && value < 113) {
				int8_t val = (((value-16)/2)-24);
				Music.setSemitone2(val);
			} else if (value < 16) {
				Music.setSemitone2(-24);				
			} else {
				Music.setSemitone2(24);
			}
			break;
		case SEMITONE3:
			if(15 < value && value < 113) {
				int8_t val = (((value-16)/2)-24);
				Music.setSemitone3(val);
			} else if (value < 16) {
				Music.setSemitone3(-24);				
			} else {
				Music.setSemitone3(24);
			}
			break;
		case GAIN1:
			Music.setGain1(value / 127.0);
			break;
		case GAIN2:
			Music.setGain2(value / 127.0);
			break;
		case GAIN3:
			Music.setGain3(value / 127.0);
			break;
		case WAVEFORM:
			Music.setWaveform(value / 8);
			break;
		case WAVEFORM1:
			Music.setWaveform1(value / 8);
			break;
		case WAVEFORM2:
			Music.setWaveform2(value / 8);
			break;
		case WAVEFORM3:
			Music.setWaveform3(value / 8);
			break;
		case FM2:
			Music.setFM2(value);
			break;
		case ENV_ATTACK:
			Music.setAttack(value);
			break;
		case ENV_DECAY:
			Music.setDecay(value);
			break;
		case ENV_SUSTAIN:
			Music.setSustain(value);
			break;
		case ENV_RELEASE:
			Music.setRelease(value);
			break;
		default:
			break;
	} 
}


void MMidi::programChange(uint8_t channel, uint8_t number) {
	// Write code here for Program Change 
}


void MMidi::channelPressure(uint8_t channel, uint8_t pressure) {
	// Write code here for Channel Pressure 
}


void MMidi::pitchWheel(uint8_t channel, uint8_t highBits, uint8_t lowBits) {
	// Write code here for Pitch Wheel
}

#endif

#endif // close guard Music_h

