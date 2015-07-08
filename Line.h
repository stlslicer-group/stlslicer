#ifndef FILE_Line_SEEN
#define FILE_Line_SEEN

#include "ThreeDPoint.h"

class Line {
	private:
		//private members
		ThreeDPoint mPointOne;
		ThreeDPoint mPointTwo;
	
	public:
		//constructor
		Line(ThreeDPoint pointOne, ThreeDPoint pointTwo);

		ThreeDPoint getPointOne() const;
		ThreeDPoint getPointTwo() const;
};

#endif

