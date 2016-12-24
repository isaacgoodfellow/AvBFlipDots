/*
bool DripDissolve::update(){

	char dupe[28][14] = {{0x00}};
	for(int x = 0; x< 28; ++x){
		for(int y =0; y < 14; ++y){
			int inc = random(1,2);
			if( x+inc < 28 ){
				dupe[x+inc][y] = mImage[x][y];
			}
		}
	}

	for(int x = 0; x< 28; ++x){
		for(int y =0; y < 14; ++y){
				mImage[x][y] = dupe[x][y];
		}
	}
  return false;

}
*/
