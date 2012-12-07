//Damp3 trying integration to get velocity
// ala Kalman filtering?

int x; //position measured [0-1023]
float af, vf //acceleration, velocity estimates
float ff // force out
float K = 1.0 //spring
float B = 10.0 //damping (dominant)
float M = 1.0 //mass

void setup(){
  Serial.begin(115200);
}

void loop(){
  x = analogRead(A0);
  ff = K*(xf-x) - B*vf; // the spring K 
  af = ff/M;
  vf += af*T; //T is cycle time
  xf += vf*T;
