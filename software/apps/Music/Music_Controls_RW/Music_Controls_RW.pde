//import oscP5.*;
//import netP5.*;
import controlP5.*;
import rwmidi.*;  // watch out for this
import processing.serial.*;

ControlP5 controlP5;

MidiInput input;

Serial port0;

boolean printChange = true;

int defaultMidiChannel = 9;

int backgroundColor = color(0,0,0);
int knobColor = color(235,103,295);

int numKnobs = 24;
int[] knobValue = new int[numKnobs];

int posX = 20;
int posY = 40;
int posW = 60;
int posH = 60;
int knobS = 40;


void setup() {
  
  size(400,400);
  smooth();
  background(0);
  
  controlP5 = new ControlP5(this);
  PFont p = createFont("Georgia",12); 
  controlP5.setControlFont(p,12);
  controlP5.setColorLabel(color(255,128));

  Textlabel labelFreq = controlP5.addTextlabel("freqLabel","FREQ",posX+posW*0+3,posY-20);
  Textlabel labelSemi = controlP5.addTextlabel("semiLabel","SEMI",posX+posW*1+4,posY-20);
  Textlabel labelDetune = controlP5.addTextlabel("detuneLabel","DETUNE",posX+posW*2-6,posY-20);
  Textlabel labelGain = controlP5.addTextlabel("gainLabel","GAIN",posX+posW*3+4,posY-20);
  Textlabel labelWave = controlP5.addTextlabel("waveLabel","WAVE",posX+posW*4+2,posY-20);

  Textlabel labelAttack = controlP5.addTextlabel("attackLabel","A",posX+16+posW*0,posY+posH*4-20);
  Textlabel labelDecay = controlP5.addTextlabel("decayLabel","D",posX+16+posW*1,posY+posH*4-20);
  Textlabel labelsustain = controlP5.addTextlabel("sustainLabel","S",posX+16+posW*2,posY+posH*4-20);
  Textlabel labelReleasek = controlP5.addTextlabel("releaseLabel","R",posX+16+posW*3,posY+posH*4-20);

  Knob freq1 = controlP5.addKnob("freq1",    0,127,64,  posX+posW*0,posY+posH*0,knobS);
  Knob semi1 = controlP5.addKnob("semi1",    -24,24,0,  posX+posW*1,posY+posH*0,knobS);
  Knob detune1 = controlP5.addKnob("detune1",0,127,64,  posX+posW*2,posY+posH*0,knobS);
  Knob gain1 = controlP5.addKnob("gain1",    0,127,127, posX+posW*3,posY+posH*0,knobS);
  Knob wave1 = controlP5.addKnob("wave1",    0,15,0,   posX+posW*4,posY+posH*0,knobS);

  Knob freq2 = controlP5.addKnob("freq2",    0,127,64,  posX+posW*0,posY+posH*1,knobS);
  Knob semi2 = controlP5.addKnob("semi2",    -24,24,0,  posX+posW*1,posY+posH*1,knobS);
  Knob detune2 = controlP5.addKnob("detune2",0,127,64,  posX+posW*2,posY+posH*1,knobS);
  Knob gain2 = controlP5.addKnob("gain2",    0,127,127, posX+posW*3,posY+posH*1,knobS);
  Knob wave2 = controlP5.addKnob("wave2",    0,15,0,   posX+posW*4,posY+posH*1,knobS);

  Knob freq3 = controlP5.addKnob("freq3",    0,127,64,  posX+posW*0,posY+posH*2,knobS);
  Knob semi3 = controlP5.addKnob("semi3",    -24,24,0,  posX+posW*1,posY+posH*2,knobS);
  Knob detune3 = controlP5.addKnob("detune3",0,127,64,  posX+posW*2,posY+posH*2,knobS);
  Knob gain3 = controlP5.addKnob("gain3",    0,127,127, posX+posW*3,posY+posH*2,knobS);
  Knob wave3 = controlP5.addKnob("wave3",    0,15,0,   posX+posW*4,posY+posH*2,knobS);

  Knob attack = controlP5.addKnob("attack",  0,127,0,   posX+posW*0, posY+posH*4, knobS);
  Knob decay = controlP5.addKnob("decay",    0,127,64,   posX+posW*1, posY+posH*4, knobS);
  Knob sustain = controlP5.addKnob("sustain",0,127,64,   posX+posW*2, posY+posH*4, knobS);
  Knob release = controlP5.addKnob("release",0,127,64,   posX+posW*3, posY+posH*4, knobS);

    
  println("print MIDI input devices:");
  println(RWMidi.getInputDeviceNames());
  input = RWMidi.getInputDevices()[0].createInput(this);
  
  println(Serial.list());
  port0 = new Serial(this, Serial.list()[0], 9600);
  
  for(int i=0; i<numKnobs; i++) {
    knobValue[i] = 0;
  }

}


void draw() {
  background(backgroundColor);
  
  
  if(port0.available() > 0) {
    //int val = port0.read();
    //float val = float(port0.read());
    char val = char(port0.read());
    println(val); 
  }
  
}


void noteOnReceived(Note note) {
  
  byte channel = byte(note.getChannel());
  byte pitch = byte(note.getPitch());
  byte velocity = byte(note.getVelocity());

  sendNoteOn(channel, pitch, velocity);
  
}

void noteOffReceived(Note note) {

  byte channel = byte(note.getChannel());
  byte pitch = byte(note.getPitch());
  byte velocity = byte(note.getVelocity());
  
  sendNoteOff(channel, pitch, velocity);
  
}

void controllerChangeReceived(rwmidi.Controller controller) {
  
  byte channel = byte(controller.getChannel());
  byte CC = byte(controller.getCC());
  byte value = byte(controller.getValue());
  
  sendControlChange(channel, CC, value);
}


void sendNoteOn(byte channel, byte pitch, byte velocity) {

  byte noteOn = byte(0x90 | channel);

  port0.write(noteOn);
  port0.write(pitch);
  port0.write(velocity);
  //println('\n' + hex(noteOn) + " " + hex(pitch) + " " + hex(velocity));

}

void sendNoteOff(byte channel, byte pitch, byte velocity) {

  byte noteOff = byte(0x80 | channel);  

  port0.write(noteOff);
  port0.write(pitch);
  port0.write(velocity);
  //println('\n' + hex(noteOff) + " " + hex(pitch) + " " + hex(velocity));

}

void sendControlChange(byte channel, byte CC, byte value) {
  
  byte controlChange = byte(0xB0 | channel);
  
  port0.clear();
  port0.write(controlChange);
  port0.write(CC);
  port0.write(value);
  //println('\n' + hex(controlChange) + " " + hex(CC) + " " + hex(value));
  
}
