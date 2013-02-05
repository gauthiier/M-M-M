//read position A0 FSR A1

void setup(){
  Serial.begin(9600);
  pinMode(A0,INPUT);
  //for FSR
  pinMode(A1,INPUT);
  digitalWrite(A1,HIGH);
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
}

void loop(){
  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.println(analogRead(A1));
}
