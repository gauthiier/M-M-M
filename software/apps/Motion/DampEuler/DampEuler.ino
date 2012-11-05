//Damp Euler

#define n 10 //number in buffer "window size"
// finite difference with n samples between x(i)
int x[n]; //last n samples of position
int index = 0;
float v; // estimate of velocity
byte c;

void setup(){
  Serial.begin(9600);
  for(int i=0; i<n; i++) x[i]=analogRead(A0);
}

void loop(){
  x[index] = analogRead(A0); //position measured
  v = (x[index] - x[index++%n])/n;
  if(index > n-1) index = 0;
  v = buff[index] - buff[(index-n)%n];
  if(c++==0)Serial.println(v);
}
  


