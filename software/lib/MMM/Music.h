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

#include "Arduino.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h> 
#include <hardwareSerial.h>

#include "Wavetable.h"


////////////////////////////////////
//
// SET NUMBER OF OSCILLATORS HERE.
// SHOULD BE 1, 2 or 3
//
////////////////////////////////////
//#define NUM_OSCILLATORS 3  //edited BV 29Jan13.


// current sample rate is 15625 as defined in the init() section
#define SAMPLE_RATE 15625

#ifndef NUM_OSCILLATORS
	#define NUM_OSCILLATORS 1
#elif (NUM_OSCILLATORS == 1)||(NUM_OSCILLATORS == 2)||(NUM_OSCILLATORS == 3)
#else
#error NUM_OSCILLATORS shall be 1, 2 or 3
#endif

// Maximum possible value for amplification envelope
#define MAX_ENV_GAIN 65535



// Table of MIDI note values to frequency in Hertz
prog_uint16_t hertsTable[] PROGMEM = {8,8,9,9,10,10,11,12,12,13,14,15,16,17,18,19,20,21,23,24,25,27,29,30,32,34,36,38,41,43,46,48,51,54,58,61,65,69,73,77,82,87,92,97,103,109,116,123,130,138,146,155,164,174,184,195,207,219,233,246,261,277,293,311,329,349,369,391,415,440,466,493,523,554,587,622,659,698,739,783,830,880,932,987,1046,1108,1174,1244,1318,1396,1479,1567,1661,1760,1864,1975,2093,2217,2349,2489,2637,2793,2959,3135,3322,3520,3729,3951,4186,4434,4698,4978,5274,5587,5919,6271,6644,7040,7458,7902,8372,8869,9397,9956,10548,11175,11839,12543};

prog_uint32_t envTimeTable[] PROGMEM = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,33,34,35,36,37,38,39,41,42,43,45,46,48,49,51,53,55,57,59,61,63,65,67,70,73,75,78,81,85,88,92,96,100,104,109,114,119,125,131,138,146,154,163,172,183,195,209,225,242,261,284,310,341,379,425,482,556,654,792,998,1342,2030,4095};

float semitoneTable[] = {0.25,0.2648658,0.2806155,0.29730177,0.31498027,0.33370996,0.35355338,0.37457678,0.39685026,0.4204482,0.44544938,0.47193715,0.5,0.5297315,0.561231,0.59460354,0.62996054,0.6674199,0.70710677,0.74915355,0.7937005,0.8408964,0.8908987,0.9438743,1.0,1.0594631,1.122462,1.1892071,1.2599211,1.3348398,1.4142135,1.4983071,1.587401,1.6817929,1.7817974,1.8877486,2.0,2.1189263,2.244924,2.3784142,2.5198421,2.6696796,2.828427,2.9966142,3.174802,3.3635857,3.563595,3.7754972,4.0};

// Defining which pins the SPI interface is connected to.
#define SPI_SCK 5
#define SPI_MOSI 3




class MMusic {    
public:
	
	// INITIALIZER
    void init();

	// AUDIO INTERRUPT SERVICE ROUTINE
	void synthInterrupt8bit();
	void synthInterrupt12bitSine();
		
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
	void pitchBend(float b); // NOT IMPLEMENTED
	
	// WAVEFORM FUNCTIONS
	void setWaveform(uint16_t waveForm);    // JUST FOR 8bit WAVEFORMS
	void setWaveform1(uint16_t waveForm);   //
	void setWaveform2(uint16_t waveForm);   //
	void setWaveform3(uint16_t waveForm);   //
	
	// GAIN FUNCTIONS
	//void setGainFloat(float value); // 0.0 - 1.0
	//void setGain16bit(uint16_t value); // 0 - 65535
	//void setGain(uint16_t value); // 0 - 65535
	void setGain(float value); // 0.0 - 1.0         USE THIS
	//void setGain1(uint16_t value); // 0 - 65535 
	//void setGain2(uint16_t value); // 0 - 65535
	//void setGain3(uint16_t value); // 0 - 65535
	//float getGainFloat();       // 0.0 - 1.0        USE THIS
	void setGain1(float value); // 0.0 - 1.0        USE THIS
	void setGain2(float value); // 0.0 - 1.0        USE THIS
	void setGain3(float value); // 0.0 - 1.0        USE THIS
	//float getGain1Float();       // 0.0 - 1.0        USE THIS
	//float getGain2Float();       // 0.0 - 1.0        USE THIS
	//float getGain3Float();       // 0.0 - 1.0        USE THIS
	float getGain();       // 0.0 - 1.0        USE THIS
	float getGain1();       // 0.0 - 1.0        USE THIS
	float getGain2();       // 0.0 - 1.0        USE THIS
	float getGain3();       // 0.0 - 1.0        USE THIS
	//uint16_t getGain();
	//uint16_t getGain1();
	//uint16_t getGain2();
	//uint16_t getGain3();

	// NOTE FUNCTIONS
	void noteOn(uint8_t note, uint8_t vel); // 0 - 255
	void noteOn(uint8_t note); // 0 - 255
	void noteOff(uint8_t note); // 0 - 255
	void noteOff();
	uint16_t getNoteFrequency(uint8_t note); // 0 - 127    CHECK THIS OUT
	
	// ENVELOPE FUNCTIONS
	void enableEnvelope();
	void disableEnvelope();
	void setEnvStage(uint8_t stage); // 0 - 4
	
	void setAttack16bit(uint16_t att); // 0 - 65535
	void setDecay16bit(uint16_t dec); // 0 - 65535
	void setSustain16bit(uint16_t sus); // 0 - 65535
	void setRelease16bit(uint16_t rel); // 0 - 65535
	
	void setAttack(uint8_t att); // 0 - 127             USE THESE ONES
	void setDecay(uint8_t dec); // 0 - 127              USE THESE ONES
	void setSustain(uint8_t sus); // 0 - 127            USE THESE ONES
	void setRelease(uint8_t rel); // 0 - 127            USE THESE ONES
	
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



/////////////////////////////////////////////////////////
//
//	8 BIT WAVETABLE - AUDIO INTERRUPT SERVICE ROUTINE
//
/////////////////////////////////////////////////////////


void inline MMusic::synthInterrupt8bit()
{
	PORTD &= ~(1<<3);
	
	// Frame sync low for SPI (making it low here so that we can measure lenght of interrupt with scope)
	PORTD &= ~(1<<6);
	
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
		
		// No gain
		else if (envStage == 0) {
			env = 0;
			accumulator1 = 0;
			accumulator2 = 0;
			accumulator3 = 0;
		}
		
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
	PORTD |= (1<<6);
	
}




/////////////////////////////////////////////////////////
//
//	12 BIT SINEWAVE - AUDIO INTERRUPT SERVICE ROUTINE
//
/////////////////////////////////////////////////////////


void MMusic::synthInterrupt12bitSine()
{
	// Frame sync low for SPI (making it low here so that we can measure lenght of interrupt with scope)
	PORTD &= ~(1<<6);
	
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
	PORTD |= (1<<6);
	
	// Frame sync high
	PORTD |= (1<<3);
	
	
}


MMusic Music;

//////////////////////////////////////////////////////////
//
// AUDIO INTERRUPT. USE EITHER 8bit or 12bitSine VERSION
// COMMENT OUT THE ONE YOU ARE NOT USING
//
//////////////////////////////////////////////////////////
ISR(TIMER2_COMPA_vect) { // timer 2 is audio interrupt timer
	
	OCR2A = 127; // don't change this
	
	Music.synthInterrupt8bit();
	
	//	Music.synthInterrupt12bitSine();
	
}




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
	DDRD |= (1 << DDD6) | (1 << DDB3);
	
	// set up SPI port
	SPCR = 0x50;
	SPSR = 0x01;
	
	// DAC frame sync HIGH, so that the SPI port doesn't start wirting straight away
	PORTD |= (1<<6);
	
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

/*
 void MMusic::setGainFloat(float value)
 {
 gain = uint16_t(value * 65535);
 gain1 = gain;
 gain2 = gain;
 gain3 = gain;
 }
 
 
 void MMusic::setGain16bit(uint16_t value)
 {
 gain = value;
 gain1 = value;
 gain2 = value;
 gain3 = value;
 }
 */

void MMusic::setGain(float value)
{
	gain = uint16_t(value * 65535);
	gain1 = gain;
	gain2 = gain;
	gain3 = gain;
}

/*
 void MMusic::setGain(uint16_t value)
 {
 gain = value;
 gain1 = value;
 gain2 = value;
 gain3 = value;
 }
 */

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

/*
 void MMusic::setGain1(uint16_t value)
 {
 gain1 = value;
 }
 
 
 void MMusic::setGain2(uint16_t value)
 {
 gain2 = value;
 }
 
 
 void MMusic::setGain3(uint16_t value)
 {
 gain3 = value;
 }
 */

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

/*
 float MMusic::getGainFloat()
 {
 return float(gain)/65535.0;
 }
 
 
 float MMusic::getGain1Float()
 {
 return float(gain1)/65535.0;
 }
 
 
 float MMusic::getGain2Float()
 {
 return float(gain2)/65535.0;
 }
 
 
 float MMusic::getGain3Float()
 {
 return float(gain3)/65535.0;
 }
 
 
 uint16_t MMusic::getGain()
 {
 return gain;
 }
 
 
 uint16_t MMusic::getGain1()
 {
 return gain1;
 }
 
 
 uint16_t MMusic::getGain2()
 {
 return gain2;
 }
 
 
 uint16_t MMusic::getGain3()
 {
 return gain3;
 }
 
 */


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
	memcpy_P(&frequency16bit, &hertsTable[notePlayed],2);
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
	memcpy_P(&frequency16bit, &hertsTable[notePlayed],2);
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


void MMusic::setAttack16bit(uint16_t att)
{
	attack = att;
}


void MMusic::setDecay16bit(uint16_t dec)
{
	decay = dec;
}


void MMusic::setSustain16bit(uint16_t sus)
{
	sustain = sus;
}


void MMusic::setRelease16bit(uint16_t rel)
{
	release = rel;
}


void MMusic::setAttack(uint8_t att)
{
	if(att>127) att = 127;
	memcpy_P(&attack, &envTimeTable[127 - att],2);
	//attack = envTimeTable[127 - att];
}


void MMusic::setDecay(uint8_t dec)
{
	if(dec>127) dec = 127;
	memcpy_P(&decay, &envTimeTable[127 - dec],2);
	//decay = envTimeTable[127 - dec];
}


void MMusic::setSustain(uint8_t sus)
{
	sustain = ((sus * MAX_ENV_GAIN)/128);	
}


void MMusic::setRelease(uint8_t rel)
{
	if(rel>127) rel = 127;
	memcpy_P(&release, &envTimeTable[127 - rel],2);
	//release = envTimeTable[127 - rel];
}


void MMusic::setVelSustain(uint8_t vel)
{
	velSustain = vel * (sustain / 128);	
}


void MMusic::setVelPeak(uint8_t vel)
{
	velPeak = vel * (MAX_ENV_GAIN / 128);	
}








#endif // close guard
