String[] knobName = {"FREQ1",
                      "SEMI1",
                      "DETUNE1",
                      "GAIN1",
                      "WAVE1",
                      "FREQ2",
                      "SEMI2",
                      "DETUNE2",
                      "GAIN2",
                      "WAVE2",
                      "FREQ3",
                      "SEMI3",
                      "DETUNE3",
                      "GAIN3",
                      "WAVE3",
                      "ATTACK",
                      "DECAY",
                      "SUSTAIN",
                      "RELEASE",
                      "DETUNE_ALL",
                      "WAVE_ALL"
                    };
                    
String[] waveform = {"SINE",
                      "SQUARE",
                      "PULSE",
                      "TRIANGLE",
                      "SAW",
                      "FUZZ",
                      "DIGI1",
                      "DIGI2",
                      "DIGI3",
                      "DIGI4",
                      "NOISE",
                      "DIGI6",
                      "TAN1",
                      "TAN2",
                      "TAN3",
                      "TAN4"
                    };
                    
byte[] knobMidiCC = {10,11,12,13,14,20,21,22,23,24,30,31,32,33,34,114,115,116,117,4,5};


void freq1(int val)
{
  val = (int)val;
  int knob = 0;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + (int)(pow(2,(knobValue[knob]-69)/12.0)*440) + " Hz");
    //(2^((p-69)/12))*440
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void semi1(int val)
{
  val = (int)val;
  int knob = 1;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    int semi =(knobValue[knob]+24)*2+16;
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)semi);
  }
}

void detune1(int val)
{
  val = (int)val;
  int knob = 2;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void gain1(int val)
{
  val = (int)val;
  int knob = 3;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void wave1(int val)
{
  val = (int)val;
  int knob = 4;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob] + " (" + waveform[knobValue[knob]] + ")");
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)(knobValue[knob]*8));
  }
}

void freq2(int val)
{
  val = (int)val;
  int knob = 5;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + (int)(pow(2,(knobValue[knob]-69)/12.0)*440) + " Hz");
    //(2^((p-69)/12))*440
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void semi2(int val)
{
  val = (int)val;
  int knob = 6;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    int semi =(knobValue[knob]+24)*2+16;
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)semi);
  }
}

void detune2(int val)
{
  val = (int)val;
  int knob = 7;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void gain2(int val)
{
  val = (int)val;
  int knob = 8;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void wave2(int val)
{
  val = (int)val;
  int knob = 9;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob] + " (" + waveform[knobValue[knob]] + ")");
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)(knobValue[knob]*8));
  }
}

void freq3(int val)
{
  val = (int)val;
  int knob = 10;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + (int)(pow(2,(knobValue[knob]-69)/12.0)*440) + " Hz");
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void semi3(int val)
{
  val = (int)val;
  int knob = 11;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    int semi =(knobValue[knob]+24)*2+16;
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)semi);
  }
}

void detune3(int val)
{
  val = (int)val;
  int knob = 12;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void gain3(int val)
{
  val = (int)val;
  int knob = 13;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void wave3(int val)
{
  val = (int)val;
  int knob = 14;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob] + " (" + waveform[knobValue[knob]] + ")");
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)(knobValue[knob]*8));
  }
}

void attack(int val)
{
  val = (int)val;
  int knob = 15;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void decay(int val)
{
  val = (int)val;
  int knob = 16;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void sustain(int val)
{
  val = (int)val;
  int knob = 17;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}

void release(int val)
{
  val = (int)val;
  int knob = 18;
  if(knobValue[knob] != val) {
    knobValue[knob] = val;
    if(printChange) println(knobName[knob] + " is: " + knobValue[knob]);
    sendControlChange((byte)0, (byte)knobMidiCC[knob], (byte)knobValue[knob]);
  }
}


