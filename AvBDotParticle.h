#pragma once
#include "arduino.h"
#include "AvBFlipDots.h"
class AvBDotParticle{
	
	
	public:
		float x, y, vx, vy;

	void init();
	void update();

};