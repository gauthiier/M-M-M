#include <Motion.h>
#include <Motor.h>

char buf[16] = "";

char b = 'x';
String  inputString = "";
boolean stringComplete = false;

float k, m, d;
int duty;

void setup() {
  MotionA.init(INPUTA0);

  MotionA.k = 0.2f;   // spring
  MotionA.m = 1.0f;   // mass
  MotionA.d = 0.02f;  // damping

  Serial.begin(9600);  
}

void loop() {
  //send force out
  if (MotionA.F > 0) MotorA.direction(FORWARD);
  else MotorA.direction(BACKWARD);
  duty = abs(MotionA.F);
  duty = min(512,duty);
  MotorA.torque(duty);
  
  //send data to be plotted by Processing "plotter"
  sprintf(buf, "%d %d %d %d", (int)MotionA.F, (int)MotionA.A, (int)MotionA.V, (int)MotionA.X);
  Serial.println(buf);  
  
  delay(10);  
  
  if(stringComplete) {
    if(b == 'k') {
      MotionA.k = convertToFloat(inputString);
    } else if(b == 'm') {
      MotionA.m = convertToFloat(inputString);
    } else if(b == 'd') {
      MotionA.d = convertToFloat(inputString);
    }    
    b = 'x';
    stringComplete = false;
    inputString = "";
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();     
    if(inChar == 'k' || inChar == 'm' || inChar == 'd') {
      b = inChar;
    } else {
      if (inChar == ';') {
        stringComplete = true;
      } else       
        inputString += inChar;
    }
  }
}

float convertToFloat(String str) {
    char buf[16] = "";
    str.toCharArray(buf, str.length() + 1);
    return atof(buf);  
}
