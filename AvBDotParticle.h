#pragma once
#include "arduino.h"
#include "AvBFlipDots.h"
class AvBDotParticle{


		float x, y, vx, vy;
		int wait, waited;
		AvBFlipDots* mBoard;

	public:

	AvBDotParticle();
	void setDots(AvBFlipDots* dots){mBoard = dots;}
	void update();
	void reset();

};
