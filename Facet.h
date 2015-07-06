#ifndef FILE_Facet_SEEN
#define FILE_Facet_SEEN

#include "ThreeDPoint.h"
#include <iostream>

class Facet {
	private:
		//private members
		ThreeDPoint mPointOne;
		ThreeDPoint mPointTwo;
		ThreeDPoint mPointThree;
	
	public:
		//constructor
		Facet(ThreeDPoint pointOne, ThreeDPoint pointTwo, ThreeDPoint pointThree);

		ThreeDPoint getPointOne() const;
		ThreeDPoint getPointTwo() const;
		ThreeDPoint getPointThree() const;

		void printAllPoints() const;


};

#endif

