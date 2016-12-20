#pragma once
#include "arduino.h"

class AvBFlipDots{

	int  mRefreshRate;
	char mImage[28][14];

	public:

	void clear();
	void setup(int refresh = 100);
	void set(int x,int y, char color);
	void set(float x, float y, char color ); //Untested
	void line(int x1,int y1,int const x2,int const y2, char color);
	void renderAndWait();
	void stamp( int x, int y, int** arr, int w, int h);

};
