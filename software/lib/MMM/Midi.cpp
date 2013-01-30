/* 
 Midi.cpp - Music library
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

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <hardwareSerial.h>
//#include <MidiTables.h>
#include <Music.h>
#include <Midi.h>

prog_uint16_t hertzTable[] PROGMEM = {8,8,9,9,10,10,11,12,12,13,14,15,16,17,18,19,20,21,23,24,25,27,29,30,32,34,36,38,41,43,46,48,51,54,58,61,65,69,73,77,82,87,92,97,103,109,116,123,130,138,146,155,164,174,184,195,207,219,233,246,261,277,293,311,329,349,369,391,415,440,466,493,523,554,587,622,659,698,739,783,830,880,932,987,1046,1108,1174,1244,1318,1396,1479,1567,1661,1760,1864,1975,2093,2217,2349,2489,2637,2793,2959,3135,3322,3520,3729,3951,4186,4434,4698,4978,5274,5587,5919,6271,6644,7040,7458,7902,8372,8869,9397,9956,10548,11175,11839,12543};

MMidi Midi;

bool midiRead = false;


void MMidi::init()
{	
	Serial.begin(115200);

	midiBufferIndex = 0;
	midiChannel = 0;

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
	
	switch(number) {
		case DETUNE:
			Music.setDetune(value/5120.0);
			break;
		case PORTAMENTO:
			//Music.setPortamento(value);  // function to be defined, also argument
			break;
		case DETUNE1:
			Music.setDetune1(value/5120.0);
			break;
		case DETUNE2:
			Music.setDetune2(value/5120.0);
			break;
		case DETUNE3:
			Music.setDetune3(value/5120.0);
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
			//Music.setGain1(uint16_t(value * 512));
			Music.setGain1(value / 127.0);
			break;
		case GAIN2:
			//Music.setGain2(uint16_t(value * 512));
			Music.setGain2(value / 127.0);
			break;
		case GAIN3:
			//Music.setGain3(uint16_t(value * 512));
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