//position and force reporting
//sends A0 (MotorA), A1 (ForceA)
//sends A3 (MotorB), A4 (ForceB)
// to Serial Monitor

// should FSR set-up be in MMM lib?
// Bill Verplank 24Jan13

void setup() 
{ 
 Serial.begin(9600);
 //set up for FSR A1 to D4
  pinMode(A1,INPUT);
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
  digitalWrite(A1,HIGH); //internal pull-up
}

void loop()
{
  Serial.print(analogRead(A0)); //positionA
  Serial.print("  ");
  Serial.println(analogRead(A1)); //forceA
}
