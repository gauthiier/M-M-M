class ScopePlot {
  
  int d = 4, s = 4; 
  int indx, max, min;
  int w, h;
  int px, py;
  int by;
  int[] values;
  int[] pixelvalues;
  String title;
  
  ScopePlot(String t, int w, int h, int x, int y, int maxval, boolean mid){
    this.title = t;
    this.w = w + d;
    this.h = h + d;
    this.indx = s;
    this.px = x - d;
    this.py = y + d;
    this.max = maxval;
    this.min = -maxval;
    noFill();
    textSize(12);
    values = new int[w / s];
    pixelvalues = new int[w / s];
    if(mid) by = h / 2; 
    else by = this.h;
  }
  
  void draw(){
    
    pushMatrix();
    
    translate(px, py);
    
    stroke(255,255,255);
    line(     -d,      h,  w + d + d,     h);
    line(      0,     -d,          0, h + d);
    line(     -d,      0,  w + d + d,     0);
    line(  w + d,  h + d,     w + d ,    -d);    
    
    fill(255,255,255);
    textSize(10);
    text(title, d, -d+2);
    noFill();
    if(by != h) {
      line(-d, by, w + d, by);
      text(Integer.toString(this.max),  w + d + d + d, 0);
      text(Integer.toString(this.min),  w + d + d + d, h + d);
    } else {      
      text(Integer.toString(this.max),  w + d + d + d, 0);
      text(Integer.toString(values.length),  w + d + d + d, h + d + d + d);
    }    
        
    int x = s;
    for(int i = 0; i < pixelvalues.length; i++) {
      stroke(127,34,255);
      line(x, by, x, by - pixelvalues[i]);
      stroke(255,34,127);
      if(i == indx - 1) {
        stroke(255);
        text(Integer.toString(values[i]),  w + d + d + d, by - pixelvalues[i]);
      }
      ellipse(x, by - pixelvalues[i], 3, 3);
      x += s;
    }
    
    
    popMatrix();    
    
  }
  
  void data(int d) {
    values[indx] = d;
    float i = (float) d / (float)this.max;
    if(by != h) pixelvalues[indx++] = (int)(i * h / 2);
    else pixelvalues[indx++] = (int)(i * h);
    indx %= (w / s) - 1;            
  }
  
}

class ScopePlotDouble extends ScopePlot {
  
  int[] values_second;
  int[] pixelvalues_second;
  
  ScopePlotDouble(String t, int w, int h, int x, int y, int maxval, boolean mid){
    super(t, w, h, x, y, maxval, mid);
    values_second = new int[values.length];
    pixelvalues_second = new int[pixelvalues.length];    
  }
  
  void data(int d0, int d1) {    
    values_second[indx] = d1;
    float i = (float) d1 / (float)this.max;
    if(by != h) pixelvalues_second[indx] = (int)(i * h / 2);
    else pixelvalues_second[indx] = (int)(i * h);
    super.data(d0);    
  }
  
  void draw() {
    
    pushMatrix();    
    
    translate(px, py);
    
    int x = s;
    for(int i = 0; i < pixelvalues_second.length; i++) {
      stroke(255,34,127);
      line(x, by, x, by - pixelvalues_second[i]);
      stroke(127,34,255);      
      if(i == indx - 1) {
        stroke(255);
        text(Integer.toString(values_second[i]),  w + d + d + d, by - pixelvalues_second[i]);
      }
      ellipse(x, by - pixelvalues_second[i], 3, 3);
      x += s;
    }
 
    popMatrix();
    
    super.draw();    
  }
  
}

class ScopePlotInteract extends ScopePlot {
  
  int[] cpoints;
  int[] cpointsvalues;
  
  int mx, my;
  
  ScopePlotInteract(String t, int w, int h, int x, int y, int maxval, boolean mid) {
    super(t, w, h, x, y, maxval, mid);
  }
  
  void draw() {
    mx = 0;
    super.draw();
  }
  
  void mdata(int mousex, int mousey) {
    if(mousex < px + w && mousex > px && mousey > py && mousey < py + h) {
      mx = (mousex - px) / s;      
      my = mousey;
      if(mx < pixelvalues.length)
        pixelvalues[mx] = (by + py) - my;
        // compute real values here
    } 
    /*
    else if((mousex > px + w &&  mousex < px + w + d) || (mousex < px && mousex > px - d) ||
            (mousey < py && mousey > py - d) || (mousey > py + h && mousey < py + h + d)) {
      px += (mousex - mx);
      py += (my - mousey);
    }
    mx = mousex;
    my = mousey;
    */
  }
}
