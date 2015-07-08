	
#include "ThreeDPoint.h"
	
//constructor definition
ThreeDPoint::ThreeDPoint(float x, float y, float z): mX{x}, mY{y}, mZ{z} {
	//extra stuff
}

//class member definitions
float ThreeDPoint::getX() const {
	return mX;
}
float ThreeDPoint::getY() const {
	return mY;
}
float ThreeDPoint::getZ() const {
	return mZ;
}

void ThreeDPoint::setX(float x){
	mX = x;
}
void ThreeDPoint::setY(float y){
	mY = y;
}
void ThreeDPoint::setZ(float z){
	mZ = z;
}
	
