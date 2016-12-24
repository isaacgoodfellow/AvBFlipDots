#include "AvBDotParticle.h"

void AvBDotParticle::update(){


	//If out of bounds, wait before coming back
	if( (x < 0 || x > 28 || y < 0 || y > 13) && wait++ > waited ){
		reset();
	} else {
		x += vx;
		y += vy;
	}

	if(mBoard != NULL)
		mBoard->set(x,y,1);

}

void AvBDotParticle::reset(){
	x = random(28);
	y = random(14);
	vx = random(-10,10)*0.1;
	vy = random(-10,10)*0.1;
	waited = 0;
	wait = random(30,200);
}

AvBDotParticle::AvBDotParticle() : mBoard(NULL){
	reset();
}
