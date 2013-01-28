import controlP5.*;
import processing.serial.*;

 //Plots
 ScopePlot       plotA;
 ScopePlot       plotB;
 ScopePlotDouble plotC;
 
 //Communication with MMM boards
 Protocol proto;
 
 //Serial port
 Serial p;
 
 //Controlers
 ControlP5 cp5;
 SliderCallback scb;
 
 // (k)
 float kmin = 0.0f;
 float kmax = 7.0f;
 float k = 0.2f;
 Slider  k_slider;
 
 // (m)
 float mmin = 0.0f;
 float mmax = 7.0f;
 float m = 1.0f;
 Slider  m_slider;

 // (d)
 float dmin = 0.0f;
 float dmax = 7.0f;
 float d = 0.02f;
 Slider  d_slider; 

void setup() {
  
  int b = 15;
  int h = (displayHeight / 4) - (3*b);
  int w = displayWidth / 2;
  
  plotA = new ScopePlot("Force", w, h, b, b + b, 512, true);
  plotB = new ScopePlot("Velocity", w, h, b, h + 4*b, 512, true);
  plotC = new ScopePlotDouble("Position Estimate", w, h, b, 2*h + 6*b, 512, true);
  
  p = new Serial(this, Serial.list()[0], 9600);
  proto = new Protocol(p);
  
  // Controls
  cp5 = new ControlP5(this);
  scb = new SliderCallback();
  
  int sw = w / 3;
  
  k_slider = cp5.addSlider("k", kmin, kmax, b, b-5, sw - b, b-5);
  k_slider.setColorForeground(color(127,34,255));
  k_slider.setColorBackground(color(50,50,50));
  k_slider.addListener(scb);
  
  m_slider = cp5.addSlider("m", mmin, mmax, 2*b + sw, b-5, sw - b, b-5);
  m_slider.setColorForeground(color(127,34,255));
  m_slider.setColorBackground(color(50,50,50));
  m_slider.addListener(scb);
  
  d_slider = cp5.addSlider("d", dmin, dmax, 3*b + 2*sw, b-5, sw - b, b-5);
  d_slider.setColorForeground(color(127,34,255)); 
  d_slider.setColorBackground(color(50,50,50));
  d_slider.addListener(scb);
  
  size(w + 60, displayHeight - (h + (3*b)));
}

void draw() {
  background(0);
  plotA.draw();
  plotB.draw();
  plotC.draw();
}

/*
void mouseDragged() 
{
  plotA.mdata(mouseX, mouseY);
  plotB.mdata(mouseX, mouseY);
  plotC.mdata(mouseX, mouseY);
}

void mouseClicked() 
{
  plotA.mdata(mouseX, mouseY);
  plotB.mdata(mouseX, mouseY);
  plotC.mdata(mouseX, mouseY);
}
*/

void serialEvent (Serial myPort) {
  proto.processData();
  plotA.data(proto.F);
  plotB.data(proto.V);
  plotC.data(proto.X - 512, proto.Xin - 512);
}

class SliderCallback implements ControlListener {
  public void controlEvent(ControlEvent ev) {
    p.write(new String(ev.controller().name()+ev.controller().value()+";"));
    //println(ev.controller().name() + ": " + ev.controller().value());    
  }
}


