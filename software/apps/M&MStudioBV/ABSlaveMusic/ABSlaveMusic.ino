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
  Music.init();
}

void loop(){
  xA = analogRead(A0); 
  xB = analogRead(A3);
  
  foutA = 2*(xB-xA); 
  MotorA.torque(foutA);
  
  foutB = 2*(xA-xB); // this will peak at x=1024/6
  MotorB.torque(foutB);  // 1/4 or 1/2 ?

}
