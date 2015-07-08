#ifndef FILE_Plane_SEEN
#define FILE_Plane_SEEN

#include "ThreeDPoint.h"

class Plane {
	private:
		//private members
		ThreeDPoint mNormal;
		ThreeDPoint mPoint;
	
	public:
		//constructor
		Plane(ThreeDPoint normal, ThreeDPoint point);

		ThreeDPoint getNormal() const;
		ThreeDPoint getPoint() const;

		
};

#endif

