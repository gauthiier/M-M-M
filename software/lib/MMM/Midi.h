/* 
 Midi.h - Music library
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

//synth parameters as MIDI controller numbers
#define ENV_ATTACK 4
#define ENV_DECAY 5
#define ENV_SUSTAIN 6
#define ENV_RELEASE 7
#define DETUNE 12
#define WAVEFORM 13

// Synth parameters used in MIDI code
#define ENV_MAX_GAIN (65536 * 4 - 1) 


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
	uint16_t midiBuffer[4];
	int midiBufferIndex;
	uint16_t frequency;
	//uint32_t midiTime;
	//bool midiNotePlayed;
	
	//synth
	//bool noteTriggered;
	//bool noteReleased;
	//bool envSustainReached;
	uint8_t notePlayed;
	//uint16_t noteFrequency;
	//uint8_t envGain; // maybe another name for the variable
	//uint32_t envAttack;
	//uint32_t envDecay;
	//uint8_t envSustain;
	//uint32_t envRelease;
	//uint32_t envTime;
	//uint32_t envTriggerTime;
	//uint32_t envReleaseTime;
	//uint32_t portamento;
	
};

extern MMidi Midi;