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
    init();
}

void MMotor::init()
{    
    if(!reg_init){
        
        //PWM, Phase and Frequency
        //Correctthese modes are preferred for motor control applications p.130
        TCCR1A = 0;
        TCCR1B |= (1 << WGM13);
        
        //direction pins are outputs
        DDRD |= (1 << PD7);
        DDRB |= (1 << PB0);
        
        reg_init = true;
    }
    
    //set period for minimal noise            
    _period(64);
    
}

void MMotor::_set_period_bits()
{
    // clear prescaler reg
    TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
    
    if(_p < RESOLUTION)                  TCCR1B |= (1 << CS10);                  // pre-s 0
    else if((_p >>= 3) < RESOLUTION)     TCCR1B |= (1 << CS11);                  // pre-s 8
    else if((_p >>= 3) < RESOLUTION)     TCCR1B |= (1 << CS11) | (1 << CS10);    // pre-s 64
    else if((_p >>= 2) < RESOLUTION)     TCCR1B |= (1 << CS12);                  // pre-s 256
    else if((_p >>= 2) < RESOLUTION)     TCCR1B |= (1 << CS12) | (1 << CS10);    // pre-s 1024
    else _p = RESOLUTION - 1,            TCCR1B |= (1 << CS12) | (1 << CS10);    // pre-s 1024
    
    ICR1 = _p;
    
}

void MMotor::_period(long ms)
{
    _p = (F_CPU * ms) / 2000000;
    _set_period_bits();
}

void MMotor::torque(int value) 
{
    
    if(_m == MOTORA) {
        DDRB |= (1 << PB1);
        TCCR1A |= (1 << COM1A1);
    } else if(_m == MOTORB) {
        DDRB |= (1 << PB2);
        TCCR1A |= (1 << COM1B1);        
    }
    
    unsigned long duty = _p * value;
    duty >>= 10;
    if(_m == MOTORA) OCR1A = duty;
    else if(_m == MOTORB) OCR1B = duty;    
    _t = value;    
    
    start();
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
    else if(_m == MOTORB && _d == BACKWARD)     PORTB |= (1 << PB0);
    else if(_m == MOTORB && _d == FORWARD)      PORTB &= ~(1 << PB0);    
}

void MMotor::stop()
{
    TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
}

void MMotor::start()
{
    _set_period_bits();
}

void MMotor::restart()
{
    TCNT1 = 0;
}

