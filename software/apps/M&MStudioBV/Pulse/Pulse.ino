//"Pulse" - small duration positive then negative force 
// parameters: F1, T1, D1, F2, T2, D2
#include <Motor.h>

void setup(){
  MotorB.init();
}

void loop(){
  //for (int i; i < 512; i + 100){
    MotorB.torque(10);
    delay (20);
    MotorB.torque(0);
    delay (150);
    MotorB.torque(-50);
    delay (40);
    MotorB.torque(0);
    delay (750);
  //}
}
