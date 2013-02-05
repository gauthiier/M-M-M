// step response of second order system
// m mass, k spring, b damping

float xPos = 0.0;
float yPos = 0.0;
float xVel = 0.0;
float T = 0.1;
float koverm = 0.1;
float boverm = 0.01;

int x, y; // variables at mouse- and screen-resolution

void setup() {  // setup() runs once
  size(800, 500);
  frameRate(30);
}
 
void draw() {  // draw() loops forever, until stopped
  xPos = width/2;
  xVel = 0.0;
background(204);
  for(int y=0; y < height; y = y +1)  {
    xVel += koverm * (mouseX - xPos) * T - boverm * xVel; //a=F/m
    xPos += xVel * T;
    point(xPos, y);
  }
}
