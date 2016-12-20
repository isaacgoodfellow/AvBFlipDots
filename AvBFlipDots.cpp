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

void AvBFlipDots::set(int x,int y, char color){
	if(x<0 || x>27) return;
	if(y<0 || y>13) return;
	mImage[x][y] = color;
}

void AvBFlipDots::line(int x1,int y1,int const x2,int const y2, char color){
}
