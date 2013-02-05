
int[] altitude = { 10, 20, 30, 40, 50, 40, 30, 20, 10, 0 };
int i;
int s = 80;

void setup() {
  size(800,100);
}
void draw(){
  background(200);
  stroke(150);
  line(0,50,799,50);
  stroke(0);
  
  for (i = 0; i < 9; i = i+1) {
    line(s*i,altitude[i],s*(i+1),altitude[i+1]);
  }
  
  line(s*9, altitude[9], s*10-1, 50);

  for (i = 0; i < 9; i = i+1) {
    ellipse(s*(i+1),altitude[i+1], 10, 10);
  }
  
  if (mousePressed == true) {
    int pos = (mouseX+40)/s;
    altitude[pos]=mouseY;
  }
}

void mouseReleased() {
  int pos = mouseX/s;
  altitude[pos]=mouseY;
}
