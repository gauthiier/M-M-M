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

// MIDI specific constants

#ifndef MIDI_CHANNEL
#define MIDI_CHANNEL 1
#endif

// SYSEX constants
#define SYSEX_LIMIT 16
#define CFO_MANUFACTURER_ID 44
#define CFO_DEVICE_GROUP_ID 3
#define SET_CHANNEL 0


//synth parameters as MIDI controller numbers
#define DETUNE 4
#define WAVEFORM 5
#define PORTAMENTO 6

#define FREQUENCY1 10
#define SEMITONE1 11
#define DETUNE1 12
#define GAIN1 13
#define WAVEFORM1 14

#define FREQUENCY2 20
#define SEMITONE2 21
#define DETUNE2 22
#define GAIN2 23
#define WAVEFORM2 24

#define FREQUENCY3 30
#define SEMITONE3 31
#define DETUNE3 32
#define GAIN3 33
#define WAVEFORM3 34

#define ENV_ATTACK 114
#define ENV_DECAY 115
#define ENV_SUSTAIN 116
#define ENV_RELEASE 117

#define ENV2_ATTACK 124
#define ENV2_DECAY 125
#define ENV2_SUSTAIN 126
#define ENV2_RELEASE 127


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
	uint8_t data;
	uint8_t midiBuffer[SYSEX_LIMIT];
	uint8_t midiChannel;
	
	int midiBufferIndex;
	uint16_t frequency;
	uint8_t notePlayed;
};

extern MMidi Midi;