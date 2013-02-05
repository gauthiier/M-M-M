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
  size(800,800);
  for(i=0;i<11;i=i+1){
    F[i]=int(random(200));
    x[i]=80*i;
  }
}

void draw(){
  background(190);
  for (i = 0; i < 10;i= i+1){
    line(x[i],F[i],x[i+1],F[i+1]);
  }

  //if (mousePressed == false){
    //test every F,x pair to see who is closest call it ibest;
    ibest = 1;
    dist = sq(F[0]-mouseY)+sq(x[0]*mouseX);
    for (i=1;i<10;i=i+1){
      if(dist > sq(F[i]-mouseY)+sq(x[i]-mouseX)){
        ibest = i;
        dist = sq(F[i]-mouseY)+sq(x[i]-mouseX);
       }
    }
    ellipse(x[ibest],F[ibest],20,20);
 // }
  
  if (mousePressed == true){
    //now use ibest to move to mouseX, mouseY
    F[ibest] = mouseY;
    x[ibest] = min(x[ibest+1],mouseX);
    x[ibest] = max(x[ibest-1],mouseX);
  }
  
}

    

