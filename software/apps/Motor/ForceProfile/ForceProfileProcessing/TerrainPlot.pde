class TerrainPlot {
  
  int d = 4; 
  float max, min;
  int w, h;
  int px, py;  
  
  float steps_per_index; // this should not exceed step_index;
  float s, step_index;
  
  String title;  
  float pixelvalues[];
  
  TerrainPlot(String t, int w, int h, int x, int y, int nbr_index, float step_index) {
    this.title = t;
    this.w = w + d;
    this.h = h + d;
    this.px = x - d;
    this.py = y + d;
    noFill();
    textSize(12);    
    this.step_index = step_index;
    this.steps_per_index = (step_index / 3);
    this.s = 3;
    /*
    
    if(step_index > steps_per_index) {
      this.s = ((float) step_index / steps_per_index);
    } else {
      this.s = step_index;
      this.steps_per_index = 1; 
    } 
   */ 
    pixelvalues = new float[(int)((nbr_index - 1) * steps_per_index) + 1];
  }
  
  void draw() {
    pushMatrix();
    
    pushMatrix();
    
    translate(px, py);
    
    stroke(255, 255, 255);
    line(     -d, h, w + d + d, h);
    line(      0, -d, 0, h + d);
    line(     -d, 0, w + d + d, 0);
    line(  w + d, h + d, w + d, -d);    

    fill(255, 255, 255);
    textSize(10);
    //text(title, d, -d+2);
    
    popMatrix();
    
    translate(px, py + h);
    
    for(int i = 0; i < pixelvalues.length; i++) {
      float y = pixelvalues[i];
      if(abs(min) > h) { 
        y = (y / abs(min)) * h;
      } 
      line(i * s, 0, i * s, y);
    }
    
    popMatrix();
  }
  
  void data(int[] forces_points) {
    
    float FF = 0;//forces[0]; // forces interpolated
    float top = 0; // terrain value (integral of forces)
    float inc; // interpolated slope ( F[i+1] - F[i] ) / s
    
    max = 0; min = 0;
    for(int i = 0; i < forces_points.length - 1; i++) {
       inc = 0.005 * (forces_points[i+1] - forces_points[i]) ;
       for(int j = 0; j < steps_per_index; j++) {
         FF += inc;
         top = top + FF;
         pixelvalues[(int)(i * steps_per_index) + j] = top;
         if(top > max) max = top;
       }
    }  
    
    for(int i = 0; i < pixelvalues.length; i++) {
      pixelvalues[i] = (int)(pixelvalues[i] - max);
      if(pixelvalues[i] < min) {
        min = pixelvalues[i];
      }
    } 
    
  }
 
}
