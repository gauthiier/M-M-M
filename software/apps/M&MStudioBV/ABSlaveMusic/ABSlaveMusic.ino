// CenterAB - both motors
// CenterA at xB, CenterB at xA?
// feels like "Slave"

#include <Motor.h>
#include <Music.h>

int duty, count, fout;
int xA, xB, foutA, foutB;

void setup(){
  MotorA.init();
  MotorB.init();
}

void loop(){
  xA = analogRead(A0); 
  xB = analogRead(A3);
  foutA = 6*(xB-xA); // this will peak at x=1024/6
  MotorA.torque(foutA);  // 1/4 or 1/2 ?

  foutB = 6*(xA-xB); // this will peak at x=1024/6
  MotorB.torque(foutB);  // 1/4 or 1/2 ?

}
