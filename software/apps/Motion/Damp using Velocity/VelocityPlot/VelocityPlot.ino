int x, v, t;  //position velocity time
#define n 10
int xtab[n]; //table of x
int i; // index for table

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
}

void loop()
{
  // if we get a valid byte, read analog ins:
  //if (Serial.available() > 0) {
    x = analogRead(A0)/4; //just for this test
    xtab[i] = x; //put it in array of x
    i = i + 1; //index to last x (9 times ago)
    if(i>9)i=0; //increment index
    v = x - xtab[i]; //difference x vs old x
    t = (t+1)%256;  
    // send sensor values:
    Serial.print(x); // sends one byte [0-255]
    Serial.print(",");
    Serial.print(v+128);
    Serial.print(",");
    Serial.println(t);
}

