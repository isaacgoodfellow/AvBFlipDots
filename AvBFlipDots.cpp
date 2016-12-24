#include "AvBFlipDots.h"
#include <math.h>

/*
	mImage Format

	First three Bytes are reserved for the header
	Last Byte reserved for the refresh bitset
	Middle 28 Bytes are each individual Row

	0x7F = All Black [0000 0000 0000 0000 0000 0000 0111 1111]
	0x00 = All White [0000 0000 0000 0000 0000 0000 0000 0000]

	Set an individual bit with 0x01 << (bit) where (bit < 7) && (bit > -1)

	Roadmap:

	Get Lines Rendering
	Get Rectangles Rendering
	Allow for fractional values to be drawn
	Get EllipsoiAvB Rendering
	Support 2 Panels
	Support N Panels
*/

void AvBFlipDots::setup(int refresh){
	mRefreshRate = refresh;
}

void AvBFlipDots::renderAndWait(){
	// Write our header and our tail to the bit stream
	//mImage 0-7 7-14

	byte transfer1[32] = {0x00};
	transfer1[0] = 0x80;
	transfer1[1] = 0x85;
	transfer1[2] = 0x01;
	for(int i = 0; i < 28; ++i){
		for(int j = 0; j < 7; j++){
			transfer1[i+3] |= ((mImage[i][j] == 1)*0x01 << j);
		}
	}
	transfer1[31] = 0x8F;
	Serial.write(transfer1, 32);

	byte transfer2[32] = {0x00};
	transfer2[0] = 0x80;
	transfer2[1] = 0x85;
	transfer2[2] = 0x02;
	for(int i = 0; i < 28; ++i){
		for(int j = 0; j < 7; j++){
			transfer2[i+3] |= ((mImage[i][j+7] == 1)*0x01 << (j));
		}
	}
	transfer2[31] = 0x8F;
	Serial.write(transfer2, 32);

	delay(mRefreshRate);
}

void AvBFlipDots::clear(){
	for(int x = 0; x < 28; x++){
		for(int y = 0; y < 14; y++){
			set(x,y,0);
		}
	}
}

void AvBFlipDots::stamp( int offx, int offy, int** arr, int w, int h){

	int CAP_A[6][8] ={
	{1,1,1,1,1,0,0,0},
	{1,1,0,0,0,1,1,1},
	{0,0,1,1,0,1,1,1},
	{0,0,1,1,0,1,1,1},
	{1,1,0,0,0,1,1,1},
	{1,1,1,1,1,0,0,0}};


	for(int x = 0; x < w; x++){
		for(int y = 0; y < h; y++){
			set(offx+x,offy+y,(CAP_A[x][y]==0));
		}
	}
}

void AvBFlipDots::set(float x, float y, char color){
	set((int)x,(int)y,color);
}

void AvBFlipDots::set(int x,int y, char color){
	if(x<0 || x>27 || y<0 || y>13) return;
	mImage[x][y] = color;
}

void AvBFlipDots::line(int x1,int y1,int const x2,int const y2, char color){
	int delta_x(x2 - x1);
 // if x1 == x2, then it does not matter what we set here
 signed char const ix((delta_x > 0) - (delta_x < 0));
 delta_x = abs(delta_x) << 1;

 int delta_y(y2 - y1);
 // if y1 == y2, then it does not matter what we set here
 signed char const iy((delta_y > 0) - (delta_y < 0));
 delta_y = abs(delta_y) << 1;

 set(x1, y1, color);

 if (delta_x >= delta_y)
 {
		 // error may go below zero
		 int error(delta_y - (delta_x >> 1));

		 while (x1 != x2)
		 {
				 if ((error >= 0) && (error || (ix > 0)))
				 {
						 error -= delta_x;
						 y1 += iy;
				 }
				 // else do nothing

				 error += delta_y;
				 x1 += ix;

				 set(x1, y1, color);
		 }
 }
 else
 {
		 // error may go below zero
		 int error(delta_x - (delta_y >> 1));

		 while (y1 != y2)
		 {
				 if ((error >= 0) && (error || (iy > 0)))
				 {
						 error -= delta_y;
						 x1 += ix;
				 }
				 // else do nothing

				 error += delta_x;
				 y1 += iy;

				 set(x1, y1, color);
		 }
 }
}

void AvBFlipDots::rect(int x1,int y1,int const w,int const h, char color){
	//Top
	line(x1,y1,w,y1,color);
	//Bottom
	line(x1,h,w,h,color);
	//Left
	line(x1,y1,x1,h,color);
	//Right
	line(w,y1,w,h,color);
}

void AvBFlipDots::circle(int x0, int y0, int radius, char color)
{
        int x = 0;
        int y = radius;
        int delta = 2 - 2 * radius;
        int error = 0;

        while(y >= 0) {
                //SetPixel(hdc,x0 + x, y0 + y,pencol);
								set(x0 + x, y0 - y,color);
                set(x0 - x, y0 - y,color);
								set(x0 + x, y0 + y,color);
								set(x0 - x, y0 + y,color);
                error = 2 * (delta + y) - 1;
                if(delta < 0 && error <= 0) {
                        ++x;
                        delta += 2 * x + 1;
                        continue;
                }
                error = 2 * (delta - x) - 1;
                if(delta > 0 && error > 0) {
                        --y;
                        delta += 1 - 2 * y;
                        continue;
                }
                ++x;
                delta += 2 * (x - y);
                --y;
        }
}

void AvBFlipDots::midPointCircle(int x, int y, int radius,int value)
{
	int rx = 0, ry = radius;
	double d = 5.0/4.0-radius;
	while(ry>rx) {
		if(d<0){
			d += 2.0*rx+3.0;
		} else {
			d += 2.0*(rx-ry)+5.0;
			ry--;
		}
 		rx++;
		set(x+rx,y+ry,value);
		set(x+ry,y+rx,value);
		set(x-rx,y+ry,value);
		set(x+ry,y-rx,value);
		set(x+rx,y-ry,value);
		set(x-ry,y+rx,value);
		set(x-rx,y-ry,value);
		set(x-ry,y-rx,value);
	}
}
