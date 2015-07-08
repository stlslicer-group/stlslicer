#ifndef FILE_Math_SEEN
#define FILE_Math_SEEN

#include "ThreeDPoint.h"
class Math {

	public:
		
		static float dotProduct(ThreeDPoint pointOne, ThreeDPoint pointTwo);

		static ThreeDPoint sub(ThreeDPoint pointOne, ThreeDPoint pointTwo);

		static ThreeDPoint scalarMultiple(float multiple, ThreeDPoint point);

		static ThreeDPoint add(ThreeDPoint pointOne, ThreeDPoint pointTwo);

};

#endif

