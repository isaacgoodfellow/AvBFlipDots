#include "AvBFlipDots.h"
#include <math.h>

AvBFlipDots::AvBFlipDots(int refresh, uint8_t clearColor, DrawMode mode){
	//Set the rate at which we send messages to the RS485 shield
	mRefreshRate = refresh;
	mDrawMode = mode;
	mClearColor = clearColor;
	mWriteColor = WHITE;

	//Allocate our image, and swap buffer for transitions
	mImageBuffer = (uint8_t *)malloc(2*28*14*sizeof(uint8_t));
	mScreenBuffer = mImageBuffer;
	mSwapBuffer = mImageBuffer+28*14;
}

void AvBFlipDots::renderAndWait(){

	// Write our header and our tail to the bit stream
	//mImage 0-7 7-14
	byte transfer1[32] = {0x00};
		byte transfer2[32] = {0x00};

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

	//Second panel: TODO make this more general to accept other types of panel arrangements
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

	for(int x = 0; x < 28; ++x){
		for(int y = 0; y < 14; ++y){
			mImage[x][y] = mClearColor;
		}
	}

	for(int i = 0; i < 28 * 14; ++i){
		mScreenBuffer[i] = 0;
	}
}

void AvBFlipDots::swapBuffers(){
	//Swaps our offscreen buffer with our onscreen buffer
	if(mSwapBuffer > mScreenBuffer){
		mScreenBuffer = mSwapBuffer;
		mSwapBuffer = mImageBuffer;
	} else {
		mSwapBuffer = mScreenBuffer;
		mScreenBuffer = mImageBuffer;
	}
}

//TODO: Refactor to use a one dimensional array so that stamp patterns can be passed in
//'Stamp' an image buffer onto our image
void AvBFlipDots::stamp( int offx, int offy, ImageBuffer* ib){

	if(ib == NULL) return;

	//TODO figure out the fiddly array logic here later
	/*
	for(int i = 0; i < ib->w * ib->h; ++i){
		set(offx+x,offy+y,ib->mImage[i]);
	}
	*/

}

void AvBFlipDots::set(int i){
	//TODO write once the access problem is solved
}

//TODO: Research other means of this switch operation (fcn pointers, etc)
void AvBFlipDots::set(int x,int y){
	if(x<0 || x>27 || y<0 || y>13) return;
	mImage[x][y] = mWriteColor;
	/*
	switch (mDrawMode) {
		case kInvert:
		mImage[x][y] = (mWriteColor==1) ? ((mImage[x][y]+1)%2) : mImage[x][y];
		break;
		default:
		mImage[x][y] = mWriteColor;
	}
	*/
}

void AvBFlipDots::set(float x, float y){
	set((int)x,(int)y);
}

void AvBFlipDots::line(int x1,int y1,int const x2,int const y2){
	int delta_x(x2 - x1);
 // if x1 == x2, then it does not matter what we set here
 signed char const ix((delta_x > 0) - (delta_x < 0));
 delta_x = abs(delta_x) << 1;

 int delta_y(y2 - y1);
 // if y1 == y2, then it does not matter what we set here
 signed char const iy((delta_y > 0) - (delta_y < 0));
 delta_y = abs(delta_y) << 1;

 set(x1, y1);

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

				 set(x1, y1);
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

				 set(x1, y1);
		 }
 }
}

void AvBFlipDots::rect(int x1,int y1,int const w,int const h){
	//Top
	line(x1,y1,w,y1);
	//Bottom
	line(x1,h,w,h);
	//Left
	line(x1,y1,x1,h);
	//Right
	line(w,y1,w,h);
}

void AvBFlipDots::floodFill(int x, int y){
	if (x < 0 || x >= 27 || y < 0 || y >= 14)
        return;
    innerFloodFill( x, y, mImage[x][y], mWriteColor);
}

void AvBFlipDots::innerFloodFill( int x, int y, int prevC, int newC)
{
    // Base cases
    if (x < 0 || x >= 27 || y < 0 || y >= 13)
        return;
    if (mImage[x][y] != prevC)
        return;
 
    // Replace the color at (x, y)
    mImage[x][y] = newC;
 
    // Recur for north, east, south and west
    innerFloodFill( x+1, y, prevC, newC);
    innerFloodFill( x-1, y, prevC, newC);
    innerFloodFill( x, y+1, prevC, newC);
    innerFloodFill( x, y-1, prevC, newC);
}

void AvBFlipDots::circle(int x, int y, int radius){
	int rx = 0, ry = radius;
	double d = 5.0/4.0-radius;
	set(x-radius,y);
	set(x+radius,y);
	set(x,y+radius);
	set(x,y-radius);
	while(ry>rx) {
		if(d<0){
			d += 2.0*rx+3.0;
		} else {
			d += 2.0*(rx-ry)+5.0;
			ry--;
		}
 		rx++;
		set(x+rx,y+ry);
		set(x+ry,y+rx);
		set(x-rx,y+ry);
		set(x+ry,y-rx);
		set(x+rx,y-ry);
		set(x-ry,y+rx);
		set(x-rx,y-ry);
		set(x-ry,y-rx);
	}
}
