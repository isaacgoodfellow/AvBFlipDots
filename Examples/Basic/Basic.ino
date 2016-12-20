#include "AvBFlipDots.h"

AvBFlipDots dots;

void setup(){
  Serial.begin(57600);
  dots.setup();
}

void loop(){
  dots.clear();
  dots.renderAndWait();
}
