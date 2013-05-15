//import oscP5.*;
//import netP5.*;
import controlP5.*;
import rwmidi.*;  // watch out for this
import processing.serial.*;

ControlP5 controlP5;
MidiInput input;
Serial port0;

boolean printChange = true;

int backgroundColor = color(0,0,0);
int knobColor = color(235,103,295);

int numKnobs = 19;
int[] knobValue = new int[numKnobs];

int posX = 20;
int posY = 40;
int posW = 60;
int posH = 60;
int knobS = 40;

long time = 0;
long lastTime = 0;
long timePassed;
long timeAllowed = 10;

int delayTime = 40;

void setup() {
  
  size(400,400);
  smooth();
  background(0);
  
  setupKnobs();
    
  //println("print MIDI input devices:");
  //println(RWMidi.getInputDeviceNames());
  input = RWMidi.getInputDevices()[0].createInput(this);
  
  //println(Serial.list());
  port0 = new Serial(this, Serial.list()[0], 9600);
}


void draw() {
  background(backgroundColor);
  writeKnobValues();
}


void keyPressed() {
  if(key=='s' || key=='S') {
    saveKnobValues();
  }
  if(key=='l' || key=='L') {
    loadKnobValues();
  }
}


void keyReleased() {
  if(key=='l' || key=='L') {
    sendMidiKnobs();
  }
}


