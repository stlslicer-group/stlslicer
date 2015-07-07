	
#include "Model.h"
	
//constructor definition
Model::Model(std::string filePath): mFilePath{filePath} {

}

bool Model::loadModel(){
	//check if model already loaded
	if (mModelLoaded){
		return true;
	}
	try {
		//use an STLParser object to load the file
		STLParser binarySTLParser{mFilePath};

		mNumberOfFacets = binarySTLParser.getNumberOfFacets();
	
		//populate the container
		int i;
		for (i=0; i<mNumberOfFacets; i++){
			mFacets.push_back(binarySTLParser.getNextFacet());
			//check whether the Facet just added contains new min or max coord
			checkExtents(mFacets.back());
		}
	
		//all facets now loaded		

		mModelLoaded = true;
		return mModelLoaded;

	} catch (FileFailedToOpenError& error){
		std::cerr << error.getErrorMessage();
		mModelLoaded = false;
		return mModelLoaded;
	}
}

bool Model::reloadModel(){
	if (!mModelLoaded){
		return (loadModel());
	}
	resetModel();
	return (loadModel());
}

void Model::resetModel(){
	//reset Facet container
	mFacets.clear();
	//reset facet count
	mNumberOfFacets = 0;
	//reset extents	
	mXMax = std::numeric_limits<float>::lowest();
	mYMax = std::numeric_limits<float>::lowest();
	mZMax = std::numeric_limits<float>::lowest();
	mXMin = std::numeric_limits<float>::max();
	mYMin = std::numeric_limits<float>::max();
	mZMin = std::numeric_limits<float>::max();
	//update mModelLoaded flag
	mModelLoaded = false;
}

void Model::checkExtents(const Facet& currentFacet){
	checkMaxMin(currentFacet.getPointOne());
	checkMaxMin(currentFacet.getPointTwo());
	checkMaxMin(currentFacet.getPointThree());
}

void Model::checkMaxMin(const ThreeDPoint& currentPoint){
	auto x = currentPoint.getX(); 
	auto y = currentPoint.getY();
	auto z = currentPoint.getZ();
	
	//check x
	if (x > mXMax){
		mXMax = x;
	} 
	if (x < mXMin){
		mXMin = x;
	}
	//check y
	if (y > mYMax){
		mYMax = y;
	} 
	if (y < mYMin){
		mYMin = y;
	}
	//check z
	if (z > mZMax){
		mZMax = z;
	} 
	if (z < mZMin){
		mZMin = z;
	}
}

std::vector<ThreeDPoint> Model::getExtents() const {
	std::vector<ThreeDPoint> extents{};
	if (!mModelLoaded){
		//return empty vector if model not loaded
		return extents;
	}
	//create min and max point
	extents.emplace_back(mXMin, mYMin, mZMin);
	extents.emplace_back(mXMax, mYMax, mZMax);
	return extents;
}

std::string Model::getFilePath() const {
	return mFilePath;
}

bool Model::isModelLoaded() const {
	return mModelLoaded;
}
	
