// Profile of forces and terrain

int n = 10; //number of values of F calculated for each s
int s = 80; //number of samples for each n
int[] F = new int[11]; //course Force values
float[] FF = new float[800]; //fine Forces interpolated
int i,j;
//int s = 80;
//int n = 10;
int pos;

void setup() {
  size(800,200); // double height to see what interpolation looks like
}


void draw() {
  background(200);
  stroke(150);
  line(0,50,n*s-1,50);
  stroke(0);
  
  for (i = 0; i <n; i = i+1 ) {
    line(s*i, F[i], s*(i+1), F[i+1]);
  }
  
 // line(s*(n-1), F[n-1], s*n, 0);
  
  for (i = 0; i <9; i = i+1) {
    ellipse(s*(i+1),F[i+1], 10, 10);
  }
  
  if (mousePressed == true) {
    pos = (mouseX+s/2)/s;
    F[pos]=mouseY;
  }
// plot seg ments of curving terrain (interpolating force?)
  for (i = 0; i <n; i = i+1) {
    line(i*s,height-F[i],(i+1)*s,height);
  }
  
}


 void mouseReleased(){
  for (i = 0; i<n; i = i+1){
      line(i,height,i+s,height-j);
  }
 }

