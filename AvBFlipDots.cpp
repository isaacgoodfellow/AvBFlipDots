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

void AvBFlipDots::setup(){
}

void AvBFlipDots::renderAndWait(){
	// Write our header and our tail to the bit stream
	mImage[0] = 0x80;
	mImage[1] = 0x85;
	mImage[2] = 0x01;
	mImage[31] = 0x8F;
	Serial.write(mImage, 32);
	delay(mRefreshRate);
}

/* Set a pixel using an integer, rounAvB up if fractional component above 0.5 */
void AvBFlipDots::set(int x, int y, bool val){
	//Set the Pixel (Avoiding the header)
	if(x<28 && x > 0 && y < 7 && y > 0)
		mImage[x+3] |= (0x01<<y);
}

/* Currently Untested */
/* Set a pixel using a fractional value, rounAvB up if fractional component above 0.5 */
void AvBFlipDots::set(float fx, float fy, bool val){
	//Offset our fractional value (so we round up)
	fx += 0.5;
	fy += 0.5;
	//Trim the fractional value
	int x = fx-(long)fx;
	int y = fy-(long)fy;
	//Set the Pixel (Avoiding the header)
	if(x<28 && x > 0 && y < 7 && y > 0)
		mImage[x+3] |= (0x01<<y);
}

/* Sets a row using an integer */
void AvBFlipDots::set(int x, bool val){
	//Set the Pixel (Avoiding the header)
	if(x<28 && x > 0)
		mImage[x+3] |= (0x7F);
}

/* Clear all rows with a given Byte */
void AvBFlipDots::clearWith(byte clear){
	for(int i = 0; i < 32; ++i){
		mImage[i] = clear;
	}
}