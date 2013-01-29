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
Motion MotionB(MOTIONB);

uint8_t lb;
uint8_t hb;
 
float   T = N * 0.004f;             // 4ms (see TCNT1)
int     xin, dx;

float MAX_POS = 1023;
float MAX_VEL = MAX_POS / T;
float MAX_ACC = MAX_VEL / T;


Motion::Motion(MOTION m){
    _m = m;
    _i = false;
    _fcb = NULL;
};

void Motion::init(SENSOR_INPUT sensor)
{        
    if(!motion_reg_init){
        //TCNT1 = 500;               //4 ms (TCNT1)
        TIMSK1 = (1 << TOIE1);
        motion_reg_init = true;    
    }
    _i = true;
    _s = sensor;
    
    // initial values
    d = 0;
    k = 1;
    m = 1;
}

/*
void Motion::set_force_callback(force_callback fcb, PHY physics) {
    _fcb = fcb;
    _fcb_phy = physics;
}
*/

/*
float Motion::calculateFAVX(int x_in)
{
	F = k * (x_in - X) - (d * V);
	//MotionA.A = MotionA.F / MotionA.m;
	V += (F / m) * T;
	X += V * T;
	return F;
}
*/

int Motion::getX()
{
	return Xin - 512;
}

// clocked at 4ms period
ISR(TIMER1_OVF_vect) {
    //TCNT1 = 500;     
    
    if(MotionA._i) {
        ADMUX = MotionA._s & 0x07; //setting the lower four bits of ADMUX to INPUT bits and upper four bits to 0000.
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC));
        lb = ADCL;
        hb = ADCH;
        
        xin = (hb << 8) | lb;
        MotionA.Xin =  xin;
                
    }
 
}
    





    /*
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
     */
    
