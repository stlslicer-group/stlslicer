#ifndef FILE_Slicer_SEEN
#define FILE_Slicer_SEEN

#include "Model.h"
#include "Plane.h"
#include "Facet.h"
#include "Line.h"
#include "Math.h"
#include "SVGWriter.h"
#include "WriterParams.h"
#include "Error.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

class Slicer {
	private:
		//private members
		const Model *mMyModel;
		int mNumberOfSlices;
		float mSliceWidth;
		std::string mFolderOutputPath;

		//private functions
		std::vector<float> computeTees(const Plane& plane, const Facet& facet);
		Line createLine(const std::vector<float>& tees, const Facet& facet);
		

	public:
		//constructor
		Slicer(const Model *myModel, int numberOfSlices, std::string folderOutputPath);
		bool slice();

};

#endif

