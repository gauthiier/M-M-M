// ProfileFx
// receives pos from Arduino
//
//
// int F[],x[i], shown as height F[x] "profile"
// then as slope of "terrain" dT = F[x]
 

// constrains x[i]<x[i+1]  -100<F<+100

int pos;  //position from Arduino
int F[] = {0,0,0,0,0,0,0,0,0,0,0};
int x[] = {1,2,3,4,5,6,7,8,9,10,11};
int i, j, ibest;
int s = 80;
int n = 10;
float dist;
float FF; // forces interpolated
float top; // terrain value (integral of forces)
float inc; // interpolated slope ( F[i+1] - F[i] ) / s

import processing.serial.*;
int lf = 10;  // Linefeed in ASCII
String myString = null;
Serial myPort; // The serial port

void setup(){
  
  println(Serial.list());  // List all the available serial ports:
  myPort = new Serial(this, Serial.list()[0], 9600);  // Open the port you are using at the rate you want:
  myPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;
  
  noFill();
  size(800,800);
  for(i=0;i<11;i=i+1){
    F[i]=0;
    x[i]=80*i;
  }
}

void draw(  ){

  
  background(200);
  stroke(150);
  line(0,100,width,100);
  line(0,200,width,200);
  for (i = 1; i < 10; i = i+1){
    line (i*80,0,i*80,200);
  }
  

  
  stroke(0);
  for (i = 0; i < 10;i= i+1){
    line(x[i],F[i]+100,x[i+1],F[i+1]+100);
  }

    //test every F,x pair to see who is closest call it ibest;
    ibest = 1;
    dist = sq(F[0]+100-mouseY)+sq(x[0]-mouseX);
    for (i=1;i<10;i=i+1){
      if(dist > sq(F[i]+100-mouseY)+sq(x[i]-mouseX)){
        ibest = i;
        dist = sq(F[i]+100-mouseY)+sq(x[i]-mouseX);
       }
    }
    ellipse(x[ibest],F[ibest]+100,20,20);

text (Integer.toString(ibest), mouseX+10, mouseY-12);
text (Integer.toString(F[ibest]), mouseX+10, mouseY);
text (Integer.toString(x[ibest]), mouseX+10, mouseY+12);
  
  if (mousePressed == true){
    //now use ibest to move to mouseX, mouseY
    x[ibest] = min(x[ibest+1],max(x[ibest-1],mouseX));
    F[ibest] = mouseY - 100;
    if (mouseY < 0) F[ibest] = -100;
    if (mouseY > 200) F[ibest] = 100;
  }
  
//plot "terrain" assuming 80 point separation of F[]'s  
  pushMatrix();
  translate(0,height/2);
  
  top = 0;
  FF = F[0];
  for (i = 0; i < n; i = i+1) {
    s = x[i+1]-x[i]+1; // increment used for plotting
    inc = 0.01*(F[i+1]-F[i])/s;
    for (j = 0; j < s; j = j+1) {
      FF = FF + inc;
      top = top + FF; // j increments of inc = F diff.
      line(x[i]+j,height,x[i]+j,top);
    }
  }    
  popMatrix();
  
 //receive pos from Arduino
while (myPort.available() > 0) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
      myString = trim(myString);
      pos = int(myString);
    }
  }
  // draw pos cursor
  stroke(150);
  line(pos,200,pos,800);

}

void keyPressed() {
  if (key == CODED) {
    if (keyCode == UP) --F[ibest];
    if (keyCode == DOWN) ++F[ibest];
    if (keyCode == RIGHT) ++x[ibest];
    if (keyCode == LEFT) --x[ibest];
  }
}


