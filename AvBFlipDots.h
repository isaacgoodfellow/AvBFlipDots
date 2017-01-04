#pragma once
#include "arduino.h"

/*
	mImage Format

	First three Bytes are reserved for the header
	Last Byte reserved for the refresh bitset
	Middle 28 Bytes are each individual Row

	0x7F = All Black [0000 0000 0000 0000 0000 0000 0111 1111]
	0x00 = All White [0000 0000 0000 0000 0000 0000 0000 0000]

	Set an individual bit with 0x01 << (bit) where (bit < 7) && (bit > -1)

	Roadmap:

	Support Transition Effects
	Support N Panels

*/

//Blend modes:
//Normal: Colors the pixel drawn to with mWriteColor
//Invert: Flips the pixel if mWriteColor is 1
typedef enum drawMode {kNormal, kInvert} DrawMode;
typedef enum stampMode {kTransparent, kOverWrite} StampMode;

//One Dimensional image
//Used for Stamps and animations
typedef struct imageBuffer{
	uint8_t *mImage;
	int w,h;
} ImageBuffer;

//Holds an animation
typedef struct animation{
	ImageBuffer *mFrames;
	int mFrameCount;
	int mLoopCount;
} Animation;

/*
	AvBFlipDots
	A black and white flipdot display using a double buffered approach
	mImageBuffer : All allocated pixels (2*screen res)
	mScreenBufer : The Image that will be transmitted to the display
	mSwapBuffer : Our background buffer, used for image effects
*/

class AvBFlipDots{

	int  mRefreshRate;
	char mImage[28][14];
	uint8_t *mImageBuffer;
	uint8_t *mScreenBuffer;
	uint8_t *mSwapBuffer;
	char mWriteColor;

	StampMode mStampMode;
	DrawMode mDrawMode;

	//Contents of the swap buffer are displayed to screen and vise-versa
	void swapBuffers();

public:

 	AvBFlipDots(int refresh = 100, DrawMode mode = kNormal);
	void clear();
	void setup(int refresh = 100);
	void drawMode(DrawMode mode){mDrawMode = mode;};
	void stampMode(StampMode mode){mStampMode = mode;};
	void fill(char color){mWriteColor= color;};
	void set(int i);
	void set(int x,int y);
	void set(float x, float y);
	void line(int x1,int y1,int const x2,int const y2);
	void rect(int x1,int y1,int const w,int const y);
	void renderAndWait();
	void stamp( int x, int y, ImageBuffer* ib);
	void circle(int x0, int y0, int radius);
	void midPointCircle(int x, int y, int radius);
};
