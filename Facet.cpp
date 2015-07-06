
#include "Facet.h"
	
//constructor definition
Facet::Facet(ThreeDPoint pointOne, ThreeDPoint pointTwo, ThreeDPoint pointThree) : mPointOne{pointOne}, mPointTwo{pointTwo}, mPointThree{pointThree} {
	//extra stuff
}

//class member definitions
ThreeDPoint Facet::getPointOne() const {
	return mPointOne;
}
ThreeDPoint Facet::getPointTwo() const {
	return mPointTwo;
}
ThreeDPoint Facet::getPointThree() const {
	return mPointThree;
}

void Facet::printAllPoints() const {
	std::cout << "Point One: \n";
	std::cout << "X: " << mPointOne.getX() << " Y: " << mPointOne.getY() << " Z: " << mPointOne.getZ() << "\n";
	std::cout << "Point Two: \n";
	std::cout << "X: " << mPointTwo.getX() << " Y: " << mPointTwo.getY() << " Z: " << mPointTwo.getZ() << "\n";
	std::cout << "Point Three: \n";
	std::cout << "X: " << mPointThree.getX() << " Y: " << mPointThree.getY() << " Z: " << mPointThree.getZ() << "\n";
}
	
