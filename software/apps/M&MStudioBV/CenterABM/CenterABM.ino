// CenterAB - both motors

//CenterA
//position on A0, pwm:D9, dir:D8,D7
//CenterB
//position on A3, pwm:D10, dir:D11,D12


#include <Motor.h>

int duty, count, fout;
int xA, xB, foutA, foutB;

void setup(){
  Serial.begin(9600);
  MotorA.init();
  MotorB.init();
}

void loop(){
   
  xA = analogRead(A0); 
  foutA = 2*(512 - xA); // this will peak at x=1024/2
  MotorA.torque(foutA);  // 1/4 or 1/2 ?

  xB = analogRead(A3);
  foutB = (512 - xB); // this will peak at x=1024/6
  MotorB.torque(foutB);  // 1/4 or 1/2 ?

    // print every 1000 cycles
  if(count++>=0){
    count=-1000;
    Serial.print(xA,DEC);
    Serial.print(" ");
    Serial.print(foutA,DEC);
    Serial.print(" ");
    Serial.print(xB,DEC);
    Serial.print(" ");
    Serial.println(foutB,DEC);
  }

}
