Ctrl c1, c2, c3;

void setup() 
{
  size(640, 360); 
  noStroke();
  c1 = new Ctrl( 100, 100, 0);
  c2 = new Ctrl( 200, 120, 100);
  c3 = new Ctrl( 300, 130, 200);
}

void draw()
{
  background(250);
  
  c1.update(mouseX, mouseY);
  c2.update(mouseX, mouseY);
  c3.update(mouseX, mouseY);
  
  c1.display();
  c2.display();
  c3.display();
  
}

class Ctrl {
  int x, y;
  int offset;
  
  Ctrl(int tx, int ty, int to) {
    x = tx;
    y = ty;
    offset = to;
  }
  
  void update(int mx, int my) {
    offset = mouseX;
  }
  void display() {
    pushMatrix();
    translate(x, y);
    fill (250);
    rotate(offset);
    fill (153);
    ellipse(offset, 0, offset/2, 2*offset);
    popMatrix();
  }
}
    
