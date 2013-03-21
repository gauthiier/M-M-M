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

#include "Arduino.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

//bool motion_reg_init = false;

Motion MotionA(MOTIONA);
Motion MotionB(MOTIONB);

int MAX_POS = 1023;

Motion::Motion(MOTION m){
    _m = m;
    _i = false;
    _fcb = NULL;
}

void Motion::init(SENSOR_INPUT sensor)
{        
    _i = true;
    _s = sensor;    
    
    tick = millis();
}

void Motion::update_position() {
    Xin = analogRead(_s); // may take some time
}

void Motion::update_mass_spring_damper() {        
    
    // todo: filtering
    
    long t = millis();
    float dt = (float)(t - tick) / 100.0f;
    
    int xin = analogRead(_s); // may take some time, put: 512 - analogRead(_s);
    
    Xin = xin;
    F = k * (xin - X) - (d * V);
    V += (F / m) * dt;
    X += V * dt;       
    
    tick = t;
}
