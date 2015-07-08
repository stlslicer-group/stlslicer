	
#include "Math.h"
	
float Math::dotProduct(ThreeDPoint pointOne, ThreeDPoint pointTwo){

	return ((pointOne.getX() * pointTwo.getX()) + (pointOne.getY() * pointTwo.getY()) + (pointOne.getZ() * pointTwo.getZ()));
}

ThreeDPoint Math::sub(ThreeDPoint pointOne, ThreeDPoint pointTwo){
	return (ThreeDPoint{(pointOne.getX() - pointTwo.getX()), (pointOne.getY() - pointTwo.getY()), (pointOne.getZ() - pointTwo.getZ())});
}

ThreeDPoint Math::scalarMultiple(float multiple, ThreeDPoint point){
	return (ThreeDPoint{(point.getX() * multiple), (point.getY() * multiple), (point.getZ() * multiple)});
}

ThreeDPoint Math::add(ThreeDPoint pointOne, ThreeDPoint pointTwo){
	return (ThreeDPoint{(pointOne.getX() + pointTwo.getX()), (pointOne.getY() + pointTwo.getY()), (pointOne.getZ() + pointTwo.getZ())});	
}


	
