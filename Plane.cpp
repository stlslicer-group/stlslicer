	
#include "Plane.h"
	
Plane::Plane(ThreeDPoint normal, ThreeDPoint point) : mNormal{normal}, mPoint{point} {
	
}

ThreeDPoint Plane::getNormal() const {
	return mNormal;
}

ThreeDPoint Plane::getPoint() const {
	return mPoint;
}
	
