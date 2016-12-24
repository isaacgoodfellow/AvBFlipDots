#include "AvBFlipDots.h"
#include "AvBDotParticle.h"
#include <vector>

AvBFlipDots dots;

AvBDotParticle mParticles[10];

void setup(){
  Serial.begin(57600);
  dots.setup(40);
  
  for(int i = 0; i < 3; ++i){
    mParticles[i].init();
  }
}


int c = 0;
void loop(){

  dots.clear();
  
  for(int x = 0; x < 28; x++){
    for(int y = 0; y < 14; y++){
      dots.set(x,y,0);
    }
  }
  
  for(int i = 0; i < 28; ++i){
    dots.set(i,(int)(7 + sin(c*0.2 + i * 0.3) * 6),1);
  }
  c++;
  dots.renderAndWait();

}
