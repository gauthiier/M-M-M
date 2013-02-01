/* 
 Motor.cpp - Motor library
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
 + author: dviid
 + contact: dviid@labs.ciid.dk 
 */

#include "Motor.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define RESOLUTION 65536

#define PD7 PORTD7
#define PB0 PORTB0
#define PB1 PORTB1
#define PB2 PORTB2

bool reg_init = false;

MMotor MotorA(MOTORA); // this is motor A
MMotor MotorB(MOTORB); // this is motor B

MMotor::MMotor(MOTOR m)
{
    _m = m;
}

void MMotor::init()
{    
        
    if(!reg_init){

        //cli();
        //direction pins are outputs
        DDRD |= (1 << PD7);        
        DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
        
        TCCR1A = (1 << COM1A1) | (1 << COM1B1);        
        //TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);        
        
        // clear the bits
        //TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
		
        TCCR1B = (1 << WGM13) | (1 << CS10);
        
        ICR1 = 512;    
        //OCR1A = 512;    
        
        reg_init = true;
		//sei();
    }
    
}


void MMotor::torque(int value) 
{	
	if(value < 0) {
		_d = BACKWARD;
	} else {
		_d = FORWARD;
	}
	value = abs(value);
	if(value > 512) value = 512;
	//else value = abs(512);
    if(_m == MOTORA) {
		OCR1A = value;
		direction(_d);
	}
    else if(_m == MOTORB) {
		OCR1B = value;
		direction(_d);
	}
    _t = value;
}

int MMotor::torque()
{
    return _t;
}

void MMotor::direction(DIRECTION d)
{
    _d = d;
    if(_m == MOTORA && _d == FORWARD)           PORTD |= (1 << PD7);
    else if(_m == MOTORA && _d == BACKWARD)     PORTD &= ~(1 << PD7);
    else if(_m == MOTORB && _d == BACKWARD)     PORTB &= ~(1 << PB0);  // The direction of FORWARD and BACKWARD is 
    else if(_m == MOTORB && _d == FORWARD)		PORTB |= (1 << PB0);   // switched for MOTORB due to hardware design 
}

void MMotor::stop()
{
    TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
}

void MMotor::start()
{
    TCCR1B = (1 << WGM13) | (1 << CS10);
}

void MMotor::restart()
{
    TCNT1 = 0;
}

