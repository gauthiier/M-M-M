// CenterAB - both motors

//CenterA at xB, CenterB at xA?
//feels like "Double Toggle"
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
  xB = analogRead(A3);
  foutA = 6*(xB-512); // this will peak at x=1024/6
  MotorA.torque(foutA);  // 1/4 or 1/2 ?

  foutB = 6*(xA-512); // this will peak at x=1024/6
  MotorB.torque(foutB);  // 1/4 or 1/2 ?

    // print every 1000 cycles
  if(count++>=0){
    count=-500;
    Serial.print(xA,DEC);
    Serial.print(" ");
    Serial.print(foutA,DEC);
    Serial.print(" ");
    Serial.print(xB,DEC);
    Serial.print(" ");
    Serial.println(foutB,DEC);
  }

}
