
// Click within the image to change 
// the value of the rectangle

int value = 20;

void setup(){
  size(300,400);
  stroke(value);
  background(250);
}

void draw(){
  value = mouseX;
  fill(value);
  stroke(value-100);
}

void mouseReleased() {
    ellipse(mouseX,mouseY,20,20);
}

