//position
//sends A0 (MotorA), A3 (MotorB) to Serial Monitor

void setup() 
{ 
 Serial.begin(9600);
}

void loop()
{
  Serial.print(analogRead(A3));
  Serial.print("  ");
  Serial.println(analogRead(A0));
}
