#include "AvBFlipDots.h"
#include "AvBDotParticle.h"
#include <vector>

AvBFlipDots dots;
const int N = 4;

class HanaBi{
  
  int x,y;
  int r;
  int maxR;
  int rate;
  int wait;
  int waited;
  
  public:
  
  HanaBi(){
    reset();
  }
  
  void reset(){
      x = random(28);
      y = random(14);
      r = 0;
      maxR = random(4,20);
      wait = random(20,100);
      waited = 0;
  }
  
  void update(){
    if(r++ > maxR ){
      if(waited++ > wait){
        reset();
      }
    }
    dots.midPointCircle(x,y,r,1);
  }
  
};

HanaBi fireworks[N];

void setup(){
  Serial.begin(57600);
  dots.setup(70);

}

int c = 0;
void loop(){

  dots.clear();
  for(int i = 0; i < N; ++i){
    fireworks[i].update();
  }
  dots.renderAndWait();

}
