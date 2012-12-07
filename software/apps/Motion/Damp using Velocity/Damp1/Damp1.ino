//Damp - measure velocity then f=Bv
#import <Motor.h>
int x; //position measured - then filtered
float v, f, t, xold; //velocity, force, time delta
byte c; //for debug print every 256th loop

void setup(){
  Serial.begin(9600);
  xold = analogRead(A0);
}

void loop(){
  x = analogRead(A0);
  v = x - xold; //lag v, too?
  xold += 0.1*(x-xold); //slide xold with lag
  
  if(c++==0){
    //Serial.print(xold);
    //Serial.print(" ");
    Serial.println(100*v);
  }
}
  
