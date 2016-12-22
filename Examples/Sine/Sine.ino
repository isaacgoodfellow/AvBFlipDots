#include "AvBFlipDots.h"
#include "AvBDotParticle.h"
#include <vector>
#include "font_defines.h"

AvBFlipDots dots;
int c = -8;
int ww = -6;

void setup(){
  Serial.begin(57600);
  dots.setup(100);  
}

void loop(){
  dots.clear();

  int off = 1;
  dots.stamp(off ,c,(int **)CAP_A, CAP_A_X, CAP_A_Y);
  off += 7;
  dots.stamp(off ,c,(int **)CAP_A, CAP_A_X, CAP_A_Y);
  off += 7;
  dots.stamp(off ,c,(int **)CAP_A, CAP_A_X, CAP_A_Y);
  off += 7;
  dots.stamp(off ,c,(int **)CAP_A, CAP_A_X, CAP_A_Y);

  dots.renderAndWait();
  c++;
  ww++;
  if(c==15) c = -8;
  if(ww==28) ww = -6;

}
