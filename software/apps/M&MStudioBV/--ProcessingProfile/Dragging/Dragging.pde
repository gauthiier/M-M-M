// two-dimensional array?
// i = 1, 8;
// int F[], // shown an height
// x[i], // 

// constrain x[i]<x[i+1]??

int F[] = {0,0,0,0,0,0,0,0,0,0,0};
int x[] = {1,2,3,4,5,6,7,8,9,10,11};
int i, ibest;
float dist;

void setup(){
  noFill();
  size(800,800);
  for(i=0;i<11;i=i+1){
    F[i]=int(random(-100,100));
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
}

    

