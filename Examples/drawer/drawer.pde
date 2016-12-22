int XRES = 28;
int YRES = 14; 
int[][] colors;
int w = 30;
int f = 0;

void setup(){
  size(XRES*30,YRES*30);
  colors = new int[28][14];
  colorMode(RGB, 3);

}

void draw(){
  for(int x= 0; x < XRES; ++x){
    for(int y=0; y < YRES; ++y){
      fill(colors[x][y]);
      rect(x * w, y * w, w, w);
    }
  }
}

void mousePressed(){
  int x = mouseX / 30;
  int y = mouseY / 30;
  colors[x][y] = f;

}

void clear(){
  for(int x= 0; x < XRES; ++x){
    for(int y=0; y < YRES; ++y){
      colors[x][y] = 3;
    }
  }
}

void keyPressed(){
  if(key == ' '){
    clear();
  } else if(key =='1') {
    f = 0;
  } else if(key =='2') {
    f = 1;  
  } else if(key =='3') {
    f = 2;
  } else if(key =='4') {
    f = 3;  
  } else {
    printBoard();
  }
}

void printBoard(){
  int xMax = 0, yMax = 0;
  for(int x = 0; x < 28; ++x){
    for(int y = 0; y < 14; ++y){
      if(x>xMax && colors[x][y] < 3){ xMax = x+2;}
      if(y>yMax && colors[x][y] < 3){ yMax = y+1;}
    }
  }
  
  println(xMax);
  println(yMax);
  for(int x = 0; x < xMax; ++x){
    print("{");
    for(int y = 0; y < yMax; ++y){
      print(""+colors[x][y]);
      if(y!=yMax-1)print(",");
    }
    if(x != x-1){
      print("},");
    }
    print("\n"); 
  }  
}
