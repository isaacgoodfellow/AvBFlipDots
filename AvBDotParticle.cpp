#include "AvBDotParticle.h"

void AvBDotParticle::update(){

	vx = random(-10,10)*0.1;
	vy = random(-10,10)*0.1;
	x += vx;
	y += vy;

	if(x < 0) x = 27;
	if(x > 28) x = 0;
	if(y < 0) y = 7;
	if(y > 7) y = 0;



}

void AvBDotParticle::init(){
	x = random(28);
	y = random(7);
	vx = random(-10,10)*0.1;
	vy = random(-10,10)*0.1;
}
