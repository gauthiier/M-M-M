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


// current sample rate is 15625 as defined in the init() section
#define SAMPLE_RATE 15625

// Number of oscillators. Set not higher than 4.
#define NUM_OSCILLATORS 2

// Maximum possible value for amplification envelope
#define MAX_ENV_GAIN 65535

class MMusic {    
public:
	
	// INITIALIZER
    void init();

	// AUDIO INTERRUPT SERVICE ROUTINE
	void synthInterrupt();
		
	// FREQUENCY AND DETUNE FUNCTIONS
	void setFrequency(float frequency);
	void setFrequency1(float frequency1);
	void setFrequency2(float frequency2);
	void setFrequency3(float frequency3);
	void setDetune(float detune);
	void setDetune2(float detune);
	void setDetune3(float detune);
	
	// WAVEFORM FUNCTIONS
	void setSine();
	void setSaw();
	void setSquare();
	
	// GAIN FUNCTIONS
	void setGainFloat(float value); // 0.0 - 1.0
	void setGain16bit(uint16_t value); // 0 - 65535
	void setGain(uint16_t value); // 0 - 65535
	void setGain(float value); // 0.0 - 1.0
	void setGain1(uint16_t value); // 0 - 65535 
	void setGain2(uint16_t value); // 0 - 65535
	void setGain3(uint16_t value); // 0 - 65535
	void setGain1(float value); // 0.0 - 1.0 
	void setGain2(float value); // 0.0 - 1.0
	void setGain3(float value); // 0.0 - 1.0
	float getGainFloat();
	uint16_t getGain();

	// NOTE FUNCTIONS
	void noteOn(uint8_t note, uint8_t vel); // 0 - 255
	void noteOn(uint8_t note); // 0 - 255
	void noteOff(uint8_t note); // 0 - 255
	void noteOff();
	
	// ENVELOPE FUNCTIONS
	void enableEnvelope();
	void disableEnvelope();
	void setEnvStage(uint8_t stage); // 0 - 4
	
	void setAttack16bit(uint16_t att); // 0 - 65535
	void setDecay16bit(uint16_t dec); // 0 - 65535
	void setSustain16bit(uint16_t sus); // 0 - 65535
	void setRelease16bit(uint16_t rel); // 0 - 65535
	
	void setAttack(uint8_t att); // 0 - 127
	void setDecay(uint8_t dec); // 0 - 127
	void setSustain(uint8_t sus); // 0 - 127
	void setRelease(uint8_t rel); // 0 - 127	
	
	void setVelSustain(uint8_t vel); // 0 -255

	
	
private:
	
	// WAVEFORM VARIABLES
	uint8_t waveForm;
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
	float detune2;
	float detune3;
	
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
	
	// NOTE VARIABLE
	uint8_t notePlayed;
	
	// final sample that goes to the DAC    
	uint32_t sample;
	
	// the two bytes that go to the DAC over SPI
	uint8_t dacSPI0;
	uint8_t dacSPI1;
    
};

extern MMusic Music;
