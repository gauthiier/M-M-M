// Velosity sends only one byte values

int x, v, t;  //position velocity time

#define n 10
int xtab[n]; //table of x
int i; // index for table

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  establishContact();  // send a byte to establish contact until receiver responds
}

void loop()
{
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    x = analogRead(A0)/4;
    xtab[i] = x; //put it in array of x
    i = i + 1; //index to last x (9 times ago)
    if(i>9)i=0; //increment index
    v = x - xtab[i]; //difference x vs old x
    t = (t+1)%256;  
    // send sensor values:
    Serial.write(x);
    Serial.write(",");
    Serial.write(v+128);
    Serial.write(",");
    Serial.write(t);              
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0,0");   // send an initial string
    delay(300);
  }
}

