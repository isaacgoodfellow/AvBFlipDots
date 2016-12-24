#pragma once
#include "arduino.h"

class AvBFlipDots{

	int  mRefreshRate;

	char mImage[28][14];

	public:

	void clear();
	void setup(int refresh = 100);
	void set(int x,int y, char color);
	void set(float x, float y, char color );
	void line(int x1,int y1,int const x2,int const y2, char color);
	void rect(int x1,int y1,int const w,int const y, char color);
	void renderAndWait();
	void stamp( int x, int y, int** arr, int w, int h);
	void circle(int x0, int y0, int radius, char color);
	void midPointCircle(int x, int y, int radius,int value);
};
