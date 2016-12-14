#include "arduino.h"

class AvBFlipDots{
	
	int  mRefreshRate = 70;
	byte mImage[32] = {0x00};
	
	public:
	
	void clearWith(byte clear);
	void set(int x, bool val);
	void set(float x, floaty, bool val);
	void set(int x, int y, bool val);
	void setup();
	void renderAndWait();

};