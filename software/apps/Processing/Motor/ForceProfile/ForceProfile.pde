import controlP5.*;
import processing.serial.*;

static char NEW = '!';
static char OK = '*';
static char PRINT = '&';

ForceProfilePlot fpp;
Button send;
Button print;

//Serial port
Serial p; 

void setup() {
   
  int b = 15;
  //int h = (displayHeight / 3);    (work in certain resolution)
  //int w = displayWidth / 2;       (work in certain resolution)
  int w = 720; 
  int h = 300;    
  
  println("w: " + w + " h: " + h);
 
  fpp = new ForceProfilePlot("Force Profile - Perception Terrain", w, h, b, b, 80, true);
  
  ControlP5 cp5 = new ControlP5(this);
  
  send = cp5.addButton("send");
  send.setPosition(w - 20, 2*h + 2*b + 7);
  send.setSize(35, 15);
  send.setColorForeground(color(127,34,255));
  send.setColorBackground(color(50,50,50));
  
  print = cp5.addButton("print");
  print.setPosition(w - 140, 2*h + 2*b + 7);
  print.setSize(35, 15);
  print.setColorForeground(color(127,34,255));
  print.setColorBackground(color(50,50,50));
      
  size(w + 60, 2*h + 60);
  
  p = new Serial(this, Serial.list()[0], 9600);
  
}

void draw() {
  background(0);
  fpp.draw();
  
  if(p.available() > 0) {
    String in = p.readStringUntil('\n');
    if(in != null) {
      println(in);
      String[] t = splitTokens(in);
    }
  }
  
}

void mouseDragged() {
  fpp.drag(mouseX, mouseY);
}

void mouseClicked() 
{
  fpp.click(mouseX, mouseY);
}

void mouseReleased() {
  fpp.release();
}

public void send() {
  
  send.setOff();
  
  p.write(NEW);
  println("1");
  while(p.available() <= 0);
  println("2");
  char in = p.readChar();
  println("3");
  if(in == OK) {
    println("GO!");
    int s = 800 / fpp.forces.length;
    int len = s * (fpp.forces.length - 1);
    serial_send(len);
    float dx = 1023.0f / (fpp.forces.length - 1);
    float ddx = dx / s;
    for(int i = 0; i < fpp.forces.length-1; i++) {
      float k = fpp.forces[i];
      float m = (fpp.forces[i+1] - k) / dx;  
      for(int j = 0; j < s; j++) {
        int d = (int)(k + m*j);
        serial_send(d);
      }
    }    
  }    
  
  send.setOn();
  
}

public void print() {
  println("print");
  print.setOff();
  p.write(PRINT);  
  while(p.available() <= 0); // block
  while(p.available() > 0) {
  String s = p.readStringUntil('#');
  if(s != null)
   println(s); 
  }
  send.setOn();
}

public boolean serial_send(int i) {    
  p.clear();
  char msb = (char) (i / 256);
  char lsb = (char) (i & 0xff);
  p.write(lsb);
  p.write(msb);
  while(p.available() <= 0);
  char in = p.readChar();
  return (in == OK);
}

