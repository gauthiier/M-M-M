// FSR A and B test
void setup(){
  //FSR-A
  pinMode(A1,INPUT);
  digitalWrite(A1,HIGH); //set pull-up
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
  //FSR-B
  pinMode(A4,INPUT);
  digitalWrite(A4,HIGH); //set pull-up
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  
  Serial.begin(9600);
}
void loop(){
  Serial.print(analogRead(A1));
  Serial.print(" ");
  Serial.println(analogRead(A4));
}
