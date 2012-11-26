/* 
 Motion.cpp - Motion library
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

#include "Motion.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define PB0 PORTB0

bool motion_reg_init = false;

Motion MotionA(MOTIONA);
Motion MotionB(MOTIONA);

uint8_t lb;
uint8_t hb;
int     x, xx; 
float   T = N * 0.004f; // 4ms
float   v;


Motion::Motion(MOTION m){
    _m = m;
    _i = false;
};

void Motion::init(INPUT sensor)
{        
    if(!motion_reg_init){
        TCNT1 = 1000; //4 ms 
        TIMSK1 = (1 << TOIE1);
        motion_reg_init = true;    
    }
    _i = true;
    _s = sensor;
}

void Motion::updatePhysics() 
{
    
}

int Motion::getPosition() {
    return _x;
}

float Motion::getVelocity() {
    return _v;
}

float Motion::getAcceleration() {
    return _a;
}


// clocked at 4ms period
ISR(TIMER1_OVF_vect) {
    TCNT1 = 1000;     
    
    
    
    if(MotionA._i) {
        ADMUX = MotionA._s & 0x07;
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC));
        lb = ADCL;
        hb = ADCH;
        x = (hb << 8) | lb;
        MotionA._xv[MotionA._ix] = x;
        MotionA._ix++;
        MotionA._ix %= N;        
        
        xx = x - MotionA._x;
        if(abs(xx) < 2) {            
            v = 0.0f;
        } else {
            v = xx / T;
        }
        
        MotionA._a = (v - MotionA._v) / T;        
        MotionA._v = v;
        MotionA._x = x;       
        
    }
    
    if(MotionB._i) {
        ADMUX = MotionB._s & 0x07;
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC));
        lb = ADCL;
        hb = ADCH;
        x = (hb << 8) | lb;
        MotionB._xv[MotionB._ix] = x;
        MotionB._ix++;
        MotionB._ix %= N;    
        
        
        xx = x - MotionB._x;
        if(abs(xx) < 2) {            
            v = 0;
        } else {
            v = xx / T;
        }
        
        MotionB._a = (v - MotionB._v) / T;        
        MotionB._v = v;
        MotionB._x = x;       
        
    }
    
}

