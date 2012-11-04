//Damp 2 with running average position

#define n 10 //number in buffer
int x; //position measured
float xf; // running average on n samples
int buff[n];
int index = 0;
float v, oldavg; // estimate of velocity
byte c;

void setup(){
  Serial.begin(9600);
}

void loop(){
  buff[index] = analogRead(A0);
  index++;
  if(index > n-1) index = 0;
  int acc = 0;
  for(int i=0; i<n; i++)acc+=buff[i];
  float avg = acc/n;
  v = avg - oldavg;
  oldavg = avg;
  if(c++==0)Serial.println(v);
}
  


