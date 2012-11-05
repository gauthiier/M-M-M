/* 
 Motor.h - Motor library
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

enum MOTOR{
    MOTORA = 0,
    MOTORB = 1
};

enum DIRECTION {
    FORWARD,
    BACKWARD
};

class MMotor {    

public:
    
    MMotor(MOTOR m);
    
    void init();
    
    void torque(int value);
    int torque();
    
    void direction(DIRECTION d);
    DIRECTION direction();
    
    void stop();
    void start();
    void restart();
    
private:
    
    void _period(long ms);
    void _set_period_bits();
    
    MOTOR       _m;
    DIRECTION   _d;
    int         _t;  
    long        _p;
    
};

extern MMotor MotorA;
extern MMotor MotorB;
