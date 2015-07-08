	
#include "Line.h"
	
//constructor definition
Line::Line(ThreeDPoint pointOne, ThreeDPoint pointTwo): mPointOne{pointOne}, mPointTwo{pointTwo} {

}

ThreeDPoint Line::getPointOne() const {
	return mPointOne;
}
ThreeDPoint Line::getPointTwo() const {
	return mPointTwo;
}
	
