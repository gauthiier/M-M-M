/* 
 Motion.h - Motion library
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

#include <avr/io.h>

#define N 10

typedef float (*force_callback)(float position);

enum MOTION {
    MOTIONA = 0,
    MOTIONB = 1
};

enum SENSOR_INPUT {
    INPUTA0 = 0x0000,
    INPUTA1 = 0x0001,
    INPUTA2 = 0x0010,
    INPUTA3 = 0x0011,
    INPUTA4 = 0x0100,
    INPUTA5 = 0x0101,
    INPUTA6 = 0x0110,
    INPUTA7 = 0x0111    
};


class Motion {
    
public:
    Motion(MOTION m);
    
    void init(SENSOR_INPUT sensor);
    
    void update_position();
    void update_mass_spring_damper();
        
    // raw position vector
    int _xv[N];
    int _ix;    
    
    float X, V, F;    
    float m, k, d;
    int Xin;
    
    long tick;
        
    MOTION _m;
    SENSOR_INPUT  _s;
    bool   _i;
    
    force_callback _fcb; // not used in current version
};

extern Motion MotionA;
extern Motion MotionB;