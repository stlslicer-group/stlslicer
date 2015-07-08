	
#include "Slicer.h"
	
Slicer::Slicer(const Model *myModel, int numberOfSlices, std::string folderOutputPath) : mMyModel{myModel}, mNumberOfSlices{numberOfSlices}, mFolderOutputPath{folderOutputPath} {
	//compute slice width 
	//default to cutting across in the x direction
	mSliceWidth = (myModel->getExtents()[1].getX() - myModel->getExtents()[0].getX())/numberOfSlices;
	std::cout << "The slice width is: " << mSliceWidth << "\n";
}

bool Slicer::slice(){
	
	//get information from model; able to do this as friend class
	int numberOfFacets = mMyModel-> mNumberOfFacets;
	float minXExtent = mMyModel -> mXMin;
	float maxXExtent = mMyModel -> mXMax;
	float maxYEntent = mMyModel -> mYMax;

	//compute length/width ints for output

	int xMax = 0;
	int yMax = 0;

	//set bounds for writting
	if (maxXExtent >= 0){
		 xMax = (int) (maxXExtent + 0.5);
	} else {
		xMax = (int) (maxXExtent - 0.5);
	}

	if (xMax == 0){
		xMax = 1;
	}

	std::cout << "xMax is: " << xMax << " \n";

	if (maxYEntent >= 0){
		 yMax = (int) (maxYEntent + 0.5);
	} else {
		yMax = (int) (maxYEntent - 0.5);
	}

	if (yMax == 0){
		yMax = 1;
	}

	std::cout << "yMax is: " << yMax << " \n";

	int currentPlaneIndex, currentFacetIndex;

	for (currentPlaneIndex=0; currentPlaneIndex < mNumberOfSlices; currentPlaneIndex++){
		//container for descovered line segments
		std::vector<Line> lineSegments{};
		//create plane object for current level
		Plane currentPlane{ThreeDPoint{1.0, 0.0, 0.0}, ThreeDPoint{((mSliceWidth*currentPlaneIndex) + minXExtent), 0.0, 0.0}};

		int numFacetHits = 0;
		for (currentFacetIndex=0; currentFacetIndex < numberOfFacets; currentFacetIndex++){
		
			std::vector<float> tees{computeTees(currentPlane, mMyModel->mFacets[currentFacetIndex])};
		
			//TODO beware comparing floats like this? 
			if ((std::count_if (tees.begin(), tees.end(), [](float t){return (t>= 0.0 && t<= 1.0);})) == 2){
				//create a line segment of the intersection and add to the container
				lineSegments.push_back(createLine(tees, (mMyModel->mFacets[currentFacetIndex])));
				++numFacetHits;
			}
		}
		std::cout << "Facet hits this level: " << numFacetHits << "\n";
		//if container not empty, send to the SVGWriter to be outputted to file
		if (!lineSegments.empty()){
			//make SVGWriter object
			try {
				std::string outputFile = mFolderOutputPath + "slice_" + std::to_string(currentPlaneIndex) + ".svg";
				SVGWriter myWriter{outputFile, std::move(lineSegments), xMax, yMax};
				myWriter.write();
			} catch (FileFailedToBeCreatedError &error){
				std::cerr << error.getErrorMessage();
				return false;
			}
			//print a few of the lines as a test
			/*
			std::cout << "X : " << lineSegments[0].getPointOne().getX() << " Y: " << lineSegments[0].getPointOne().getY() << "\n";
			std::cout << "X : " << lineSegments[1].getPointOne().getX() << " Y: " << lineSegments[1].getPointOne().getY() << "\n";
			std::cout << "X : " << lineSegments[2].getPointOne().getX() << " Y: " << lineSegments[2].getPointOne().getY() << "\n";
			*/
		}
	} //end plane for

	return true;
}

//precondition is that only one tee is not tee >= 0.0 && tee <= 1.0; others must be
Line Slicer::createLine(const std::vector<float>& tees, const Facet& facet){

	if (!((tees[0] >= 0.0) && (tees[0] <= 1.0))){
		//t[1] and t[2] are valid then; create the two line points
		ThreeDPoint pointOne{Math::add(Math::scalarMultiple((1-tees[1]), facet.getPointOne()), Math::scalarMultiple(tees[1], facet.getPointThree()))};
		ThreeDPoint pointTwo{Math::add(Math::scalarMultiple((1-tees[2]), facet.getPointTwo()), Math::scalarMultiple(tees[2], facet.getPointThree()))};
		return Line{pointOne, pointTwo};
		
	} else if (!((tees[1] >= 0.0) && (tees[1] <= 1.0))){
		//t[0] and t[2] are valid then; create the two line points
		ThreeDPoint pointOne{Math::add(Math::scalarMultiple((1-tees[0]), facet.getPointOne()), Math::scalarMultiple(tees[0], facet.getPointTwo()))};
		ThreeDPoint pointTwo{Math::add(Math::scalarMultiple((1-tees[2]), facet.getPointTwo()), Math::scalarMultiple(tees[2], facet.getPointThree()))};		
		return Line{pointOne, pointTwo};

	} else { //t[2] is not within the bounds
		//t[0] and t[1] are valid then; create the two line points
		ThreeDPoint pointOne{Math::add(Math::scalarMultiple((1-tees[0]), facet.getPointOne()), Math::scalarMultiple(tees[0], facet.getPointTwo()))};
		ThreeDPoint pointTwo{Math::add(Math::scalarMultiple((1-tees[1]), facet.getPointOne()), Math::scalarMultiple(tees[1], facet.getPointThree()))};
		return Line{pointOne, pointTwo};
	}
}

std::vector<float> Slicer::computeTees(const Plane& plane, const Facet& facet){
	std::vector<float> results(3);

	results[0] = Math::dotProduct(plane.getNormal(), (Math::sub(plane.getPoint(), facet.getPointOne())))/(Math::dotProduct(plane.getNormal(), (Math::sub(facet.getPointTwo(), facet.getPointOne()))));
	results[1] = Math::dotProduct(plane.getNormal(), (Math::sub(plane.getPoint(), facet.getPointOne())))/(Math::dotProduct(plane.getNormal(), (Math::sub(facet.getPointThree(), facet.getPointOne()))));
	results[2] = Math::dotProduct(plane.getNormal(), (Math::sub(plane.getPoint(), facet.getPointTwo())))/(Math::dotProduct(plane.getNormal(), (Math::sub(facet.getPointThree(), facet.getPointTwo()))));

	return results;
}	

//TODO floating point comparison
//http://stackoverflow.com/questions/17333/most-effective-way-for-float-and-double-comparison


	
