//position and force reporting
//sends A0 (MotorA), A1 (ForceA)
//sends A3 (MotorB), A4 (ForceB)
// to Serial Monitor

void setup() 
{ 
 Serial.begin(9600);
 //set up for FSR A1 to D4
  pinMode(A1,INPUT);
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
  digitalWrite(A1,HIGH); //internal pull-up
  //set up for FSR A4 to D5
  pinMode(A4,INPUT);
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  digitalWrite(A4,HIGH); //internal pull-up
}

void loop()
{
  Serial.print(analogRead(A0)); //positionA
  Serial.print("  ");
  Serial.print(analogRead(A1)); //positionA
  Serial.print("  ");
  Serial.print(analogRead(A3)); //positionA
  Serial.print("  ");
  Serial.println(analogRead(A4)); //forceA
}
