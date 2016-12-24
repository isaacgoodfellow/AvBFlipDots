# 1 "c:\\users\\isaac\\appdata\\local\\temp\\tmpwpyqtw"
#include <Arduino.h>
# 1 "C:/Users/Isaac/Documents/Arduino/Sketches/AvBFlipDotsExamples/Dissolver/Dissolver/Dissolver.ino"
#include <Arduino.h>

#include "AvBFlipDots.h"
#include "AvBDotParticle.h"
AvBFlipDots dots;

class VertLine{

  int x, y, length;

  void reset(){
    x = random(28);
    y = 0;
    length = random(1,8);
  }

  public:

  void update(){
    y += 1;
    dots.line(x,y,x,y+length,1);
    if((y-length) > 14){
      reset();
    }
  }

};

VertLine lines[3];
void setup();
void loop();
#line 31 "C:/Users/Isaac/Documents/Arduino/Sketches/AvBFlipDotsExamples/Dissolver/Dissolver/Dissolver.ino"
void setup(){

  Serial.begin(57600);
  dots.setup(70);


}

void loop(){
  dots.clear();
  for(int i = 0; i < 3; ++i){
    lines[i].update();
  }
  dots.renderAndWait();

}