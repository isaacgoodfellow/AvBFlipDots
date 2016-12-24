#pragma once
#include "arduino.h"

typedef enum DrawMode {kNormal, kInvert};

class AvBFlipDots{

	int  mRefreshRate;
	char mImage[28][14];
	char mWriteColor;
	DrawMode mDrawMode;

	public:

	void clear();
	void setup(int refresh = 100);
	void drawMode(DrawMode mode);
	void fill(char color);
	void set(int x,int y);
	void set(float x, float y);
	void line(int x1,int y1,int const x2,int const y2);
	void rect(int x1,int y1,int const w,int const y);
	void renderAndWait();
	void stamp( int x, int y, int** arr, int w, int h);
	void circle(int x0, int y0, int radius);
	void midPointCircle(int x, int y, int radius);

};
