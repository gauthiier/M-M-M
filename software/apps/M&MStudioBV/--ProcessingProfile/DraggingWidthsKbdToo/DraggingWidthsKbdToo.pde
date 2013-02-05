// arrow keys for one-pixel motion
// two-dimensional array?
// i = 1, 8;
// int F[], // shown an height
// x[i], // 

// constrain x[i]<x[i+1]??

int F[] = {0,0,0,0,0,0,0,0,0,0,0};
int x[] = {1,2,3,4,5,6,7,8,9,10,11};
int i, j, ibest;
int s = 80;
int n = 10;
float dist;
float FF; // forces interpolated
float top; // terrain value (integral of forces)
float inc; // interpolated slope ( F[i+1] - F[i] ) / s


void setup(){
  noFill();
  size(800,800);
  for(i=0;i<11;i=i+1){
    F[i]=0;
    x[i]=80*i;
  }
}

void draw(){
  background(200);
  stroke(150);
  line(0,100,width,100);
  line(0,200,width,200);
  for (i = 1; i < 10; i = i+1){
    line (i*80,0,i*80,200);
  }
  stroke(0);
  for (i = 0; i < 10;i= i+1){
    line(x[i],F[i]+100,x[i+1],F[i+1]+100);
  }

    //test every F,x pair to see who is closest call it ibest;
    ibest = 1;
    dist = sq(F[0]+100-mouseY)+sq(x[0]-mouseX);
    for (i=1;i<10;i=i+1){
      if(dist > sq(F[i]+100-mouseY)+sq(x[i]-mouseX)){
        ibest = i;
        dist = sq(F[i]+100-mouseY)+sq(x[i]-mouseX);
       }
    }
    ellipse(x[ibest],F[ibest]+100,20,20);

text (Integer.toString(ibest), mouseX+10, mouseY-12);
text (Integer.toString(F[ibest]), mouseX+10, mouseY);
text (Integer.toString(x[ibest]), mouseX+10, mouseY+12);
  
  if (mousePressed == true){
    //now use ibest to move to mouseX, mouseY
    x[ibest] = min(x[ibest+1],max(x[ibest-1],mouseX));
    F[ibest] = mouseY-100;
    
  }
  
//plot "terrain" assuming 80 point separation of F[]'s  
  pushMatrix();
  translate(0,height/2);
  /*for (i = 0; i<n; i = i+1){
      line(i*s,0,(i+1)*s,0);
      }*/
  top = 0;
  FF = F[0];
  for (i = 0; i < n; i = i+1) {
    inc = -0.001*(F[i+1]-F[i]); // increment used for plotting
//s = x[i+1] - x[i] + 1; // variable widths!
    s = x[i+1] - x[i]; // number of increments
    for (j = 0; j < s; j = j+1) {
      FF = FF + inc;
      top = top + FF; // j increments of inc = F diff.
      line(x[i]+j,height,x[i]+j,top);
    }
  }    
  popMatrix();
}

void keyPressed() {
  if (key == CODED) {
    if (keyCode == UP) --F[ibest];
    if (keyCode == DOWN) ++F[ibest];
    if (keyCode == RIGHT) ++x[ibest];
    if (keyCode == LEFT) --x[ibest];
  }
}


    

