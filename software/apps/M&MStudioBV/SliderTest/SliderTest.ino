//slider test
#include <Motor.h>
void setup(){
  Serial.begin(9600);
  MotorA.init();
}
void loop(){
  MotorA.torque(analogRead(A0));
  Serial.println(analogRead(A0));
}
  
