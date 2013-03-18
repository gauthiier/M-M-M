class ForceProfilePlot {

  int d = 4, s = 4;
  float steps = 4;  
  int max, min;
  int w, h, by;
  int px, py;

  int res = 800;

  int[] forces;
  int[] forces_pixelvalues;

  int mx, my;  

  String title;

  TerrainPlot tr; 


  ForceProfilePlot(String t, int w, int h, int x, int y, int nbr_ctrpoints, boolean terrain) {
    this.title = t;
    this.w = w + d;
    this.h = h + d;
    this.px = x - d;
    this.py = y + d;
    this.max = 512;
    this.min = -512;
    noFill();
    textSize(12);    
    this.s = 800 / nbr_ctrpoints;
    this.steps = (float)(w + 2*d) / (nbr_ctrpoints - 1);
    this.by = h / 2;
    forces = new int[nbr_ctrpoints];               // zeros???
    forces_pixelvalues = new int[nbr_ctrpoints];    
    if (terrain) 
      tr = new TerrainPlot("Terrain", w, h, x, y + h + 2 * d, nbr_ctrpoints, steps);
  }

  void draw() {

    pushMatrix();

    translate(px, py);

    stroke(255, 255, 255);
    line(     -d, h, w + d + d, h);
    line(      0, -d, 0, h + d);
    line(     -d, 0, w + d + d, 0);
    line(  w + d, h + d, w + d, -d);    

    fill(255, 255, 255);
    textSize(10);
    text(title, d, -d+2);
    noFill();
    line(-d, by, w + d, by);
    text(Integer.toString(this.max), w + d + d + d, 0);
    text(Integer.toString(this.min), w + d + d + d, h + d);

    float x = 0;
    for (int i = 0; i < forces_pixelvalues.length; i++) {

      stroke(127, 34, 255);
      line(x, by, x, by - forces_pixelvalues[i]);

      stroke(255, 34, 127);
      ellipse(x, by - forces_pixelvalues[i], 5, 5);

      if (i != 0) {
        stroke(255, 255, 255);
        line(x, by - forces_pixelvalues[i], x - steps, by - forces_pixelvalues[i - 1]);
      }

      if(steps > 20)
        text(Integer.toString(forces[i]), x, by - forces_pixelvalues[i] + (forces[i] < 0 ? 7 : -7));

      x += steps;
    }    


    if (mx > 0) {
      int e = round((float) mx / steps);
      stroke(255, 34, 127);
      line(e * steps, by - forces_pixelvalues[e], mx, my);
    }      


    popMatrix();    

    if (tr != null) tr.draw();
  }

  void forces_from_pixels() {
    for (int i = 0; i < forces_pixelvalues.length; i++) {
      forces[i] = (int)(((by - forces_pixelvalues[i]) / h * 2) * 512);
    }
  }

  void pixels_from_forces() {
    for (int i = 0; i < forces.length; i++) {      
      forces_pixelvalues[i] = (int)(((float) forces[i] / (float)this.max) * h / 2);
    }
  }


  void drag(int mousex, int mousey) {
    if (hit(mousex, mousey)) 
      position_point(mousex, mousey);
  }

  void click(int mousex, int mousey) {
    if (hit(mousex, mousey)) 
      position_point(mousex, mousey);
  }

  void release() {
    mx = -1; 
    my = -1;
  }

  void position_point(int mousex, int mousey) {
    int i = round((float) (mousex - px - d) / steps);
    forces_pixelvalues[i] = h / 2 - (mousey - py - d);
    forces[i] = (int)((((float)forces_pixelvalues[i]) / h * 2) * 512);

    my = mousey - py - d;      
    mx = mousex - px - d;          

    if (tr != null) {
      tr.data(forces_pixelvalues);
      /*
      if (i > 0) 
        tr.data(i - 1, forces_pixelvalues[i - 1], i, forces_pixelvalues[i]);
      if (i < forces_pixelvalues.length - 1)
        tr.data(i, forces_pixelvalues[i], i + 1, forces_pixelvalues[i + 1]);
      */
    }
  }

  boolean hit(int mousex, int mousey) {
    return (mousex < px + w) && (mousex > px) && (mousey > py) && (mousey < py + h);
  }
}

