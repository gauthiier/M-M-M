byte[] savedKnobValues = new byte[numKnobs];
byte[] loadedKnobValues = new byte[numKnobs];


void loadKnobValues() {
  
  loadedKnobValues = loadBytes("knobValues.txt");

  for(int i=0; i<numKnobs; i++) {
    knobValue[i] = loadedKnobValues[i];
    controlP5.controller(controllerName[i]).setValue(knobValue[i]);
  }
  println();
  println("Loaded Knob Values");  
  
}

void saveKnobValues() {

    for(int i=0;i<numKnobs;i++) {
      savedKnobValues[i] = (byte)knobValue[i];
    }
    saveBytes("knobValues.txt", savedKnobValues);
    println();
    println("Saved Knob Values");
    
}

void sendMidiKnobs() {
  
  sendControlChange((byte)0, (byte)knobMidiCC[0],(byte)knobValue[0]);
  delay(delayTime);
  //semi1(knobValue[1]);
    int semi =(knobValue[1]+24)*2+16;
    sendControlChange((byte)0, (byte)knobMidiCC[1], (byte)semi);

  delay(delayTime);
  //detune1(knobValue[2]);
    sendControlChange((byte)0, (byte)knobMidiCC[2], (byte)knobValue[2]);

  delay(delayTime);
  //gain1(knobValue[3]);
    sendControlChange((byte)0, (byte)knobMidiCC[3], (byte)knobValue[3]);

  delay(delayTime);
  //wave1(knobValue[4]);
    sendControlChange((byte)0, (byte)knobMidiCC[4], (byte)(knobValue[4]*8));

  delay(delayTime);
  //freq2(knobValue[5]);
    sendControlChange((byte)0, (byte)knobMidiCC[5], (byte)knobValue[5]);

  delay(delayTime);
  //semi2(knobValue[6]);
    semi = (knobValue[6]+24)*2+16;
    sendControlChange((byte)0, (byte)knobMidiCC[6], (byte)semi);

  delay(delayTime);
  //detune2(knobValue[7]);
    sendControlChange((byte)0, (byte)knobMidiCC[7], (byte)knobValue[7]);

  delay(delayTime);
  //gain2(knobValue[8]);
    sendControlChange((byte)0, (byte)knobMidiCC[8], (byte)knobValue[8]);

  delay(delayTime);
  //wave2(knobValue[9]);
    sendControlChange((byte)0, (byte)knobMidiCC[9], (byte)(knobValue[9]*8));
  
  delay(delayTime);
  //freq3(knobValue[10]);
    sendControlChange((byte)0, (byte)knobMidiCC[10], (byte)knobValue[10]);

  delay(delayTime);
  //semi3(knobValue[11]);
    semi =(knobValue[11]+24)*2+16;
    sendControlChange((byte)0, (byte)knobMidiCC[11], (byte)semi);

  delay(delayTime);
  //detune3(knobValue[12]);
    sendControlChange((byte)0, (byte)knobMidiCC[12], (byte)knobValue[12]);

  delay(delayTime);
  //gain3(knobValue[13]);
    sendControlChange((byte)0, (byte)knobMidiCC[13], (byte)knobValue[13]);

  delay(delayTime);
  //wave3(knobValue[14]);
    sendControlChange((byte)0, (byte)knobMidiCC[14], (byte)(knobValue[14]*8));

  delay(delayTime);
  //attack(knobValue[15]);
    sendControlChange((byte)0, (byte)knobMidiCC[15], (byte)knobValue[15]);

  delay(delayTime);
  //decay(knobValue[16]);
    sendControlChange((byte)0, (byte)knobMidiCC[16], (byte)knobValue[16]);

  delay(delayTime);
  //sustain(knobValue[17]);
    sendControlChange((byte)0, (byte)knobMidiCC[17], (byte)knobValue[17]);

  delay(delayTime);
  //release(knobValue[18]);
    sendControlChange((byte)0, (byte)knobMidiCC[18], (byte)knobValue[18]);
  
  println();
  println("Sent Knob Values over MIDI");  

}


