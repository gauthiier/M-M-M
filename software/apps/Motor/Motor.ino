//#include <TimerOne.h>

#include <Motor.h>

void setup() 
{

  MotorA.torque(500);  
  
}

void loop() 
{
  static int j = 1;
  static long cnt = 0;
  
  if(cnt == 50000) {
    j = -1;
    MotorA.direction(FORWARD);
  } else if(cnt == 0) {
    j = 1;
    MotorA.direction(BACKWARD);
  }
  cnt += j;  
  
}
  
