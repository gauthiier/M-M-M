void setup(){
  pinMode(A1,INPUT);
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW); //sets ground
  digitalWrite(A1,HIGH); //sets pull-up
}
void loop(){
  digitalWrite(A1,LOW);
  digitalWrite(4,HIGH);
  delay(1000);
  digitalWrite(A1,HIGH);
  digitalWrite(4,LOW);
  delay(1000);
}

//does D4 actually go 5v to GND?
//yes, if D4 is OUTPUT.
