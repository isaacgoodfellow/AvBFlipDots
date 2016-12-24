#include "AvBFlipDots.h"
#include "AvBDotParticle.h"
#include <vector>

AvBFlipDots dots;

int x,y;


void setup(){
  Serial.begin(57600);
  dots.setup(1);
  x = 0;
  y = 0;

}

int val = 1;
int dir = 1;
void loop(){

  dots.set(x,y,val);
  y+=dir;
  if(y > 13 || y < 0){
    x++;
    dir = -dir;
  }
  if(x > 27){
    val = -val;
    x=0;
  }
  
  dots.renderAndWait();

}
