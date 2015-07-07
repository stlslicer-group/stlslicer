#ifndef FILE_Facet_SEEN
#define FILE_Facet_SEEN

#include "ThreeDPoint.h"
#include <iostream>

class Facet {
	private:
		//private members
		ThreeDPoint mNormal;
		ThreeDPoint mPointOne;
		ThreeDPoint mPointTwo;
		ThreeDPoint mPointThree;
	
	public:
		//constructor
		Facet(ThreeDPoint normal, ThreeDPoint pointOne, ThreeDPoint pointTwo, ThreeDPoint pointThree);

		ThreeDPoint getNormal() const;
		ThreeDPoint getPointOne() const;
		ThreeDPoint getPointTwo() const;
		ThreeDPoint getPointThree() const;

		void printAllPoints() const;


};

#endif

