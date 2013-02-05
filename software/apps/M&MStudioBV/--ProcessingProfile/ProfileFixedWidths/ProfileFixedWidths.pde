// Profile of forces and terrain

int n = 10; //number of values of F calculated for each s
int s = 80; //number of samples for each n
int[] F = new int[11]; // Force values [-512 to +511] scaled for plot?
float FF; // forces interpolated
float top; // terrain value (integral of forces)
float inc; // interpolated slope ( F[i+1] - F[i] ) / s
int i,j;
int pos;
int vt = 50; //vertical translation for force curve



void setup() {
  size(800,800); // double height to see what interpolation looks like
  for(i=0;i<n+1;i=i+1){
    F[i]=0;
  }
}


void draw() {
  background(200);
  
  pushMatrix();
  translate(0,vt);  // center force plot at vt
  stroke(150);
  line(0,0,n*s-1,0); // the zero force line
  
  stroke(0); // the force segments
  for (i = 0; i <n; i = i+1 ) {
    line(s*i, F[i], s*(i+1), F[i+1]);
  }
    
  for (i = 0; i <9; i = i+1) {
    ellipse(s*(i+1),F[i+1], 10, 10);
  }
  
  if (mousePressed == true) {
    pos = (mouseX+s/2)/s;
    F[pos]=mouseY-vt;
  }
  
  popMatrix();
  pushMatrix();
  translate(0,height/2);
  /*for (i = 0; i<n; i = i+1){
      line(i*s,0,(i+1)*s,0);
      }*/
  top = 0;
  FF = F[0];
  for (i = 0; i < n; i = i+1) {
    inc = 0.001*(F[i+1]-F[i]); // increment used for plotting
    for (j = 0; j < s; j = j+1) {
      FF = FF + inc;
      top = top + FF; // j increments of inc = F diff.
      line(i*s+j,height,i*s+j,top);
    }
  }    
  popMatrix();
  
}

 /*
 void mouseReleased(){
  }
 
  // plot seg ments of curving terrain (interpolating force?)
  top = 50;
  for (i = 0; i <n; i = i+1) {
    inc = (F[i+1]-F[i])/s; // increment used for plotting
    for (j = 0; j < s; j = j+1){
      top = top + inc*j; // j increments of inc = F diff.
      line(i*s,height-top,i*s,height);
    }
  }
}
*/



