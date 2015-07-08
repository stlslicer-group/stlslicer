	
#include "Model.h"

#include "Slicer.h" //have to include in body as Slicer.h includes Model.h; circular definition
	
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

bool Model::slice(int numberOfSlices, std::string outputPath){
	
	//make sure model is loaded 
	if (!mModelLoaded){
		return false;
	}

	//create slicer object
	Slicer mySlicer{this, numberOfSlices, outputPath};
	if (!mySlicer.slice()){
		return false;
	}
	return true;
}

bool Model::reloadModel(){
	if (!mModelLoaded){
		return (loadModel());
	}
	resetModel();
	return (loadModel());
}

//TODO broken; incorrect results
bool Model::scaleModel(float scaleFactor){
	if (!mModelLoaded){
		return false;
	}
	int i;
	for (i=0; i < mNumberOfFacets; i++){
		//for each facet
		//multiply each of its point's coords by scaleFactor
		mFacets[i].getPointOne().setX((mFacets[i].getPointOne().getX() * scaleFactor));
		mFacets[i].getPointOne().setY((mFacets[i].getPointOne().getY() * scaleFactor));
		mFacets[i].getPointOne().setZ((mFacets[i].getPointOne().getZ() * scaleFactor));

		mFacets[i].getPointTwo().setX((mFacets[i].getPointTwo().getX() * scaleFactor));
		mFacets[i].getPointTwo().setY((mFacets[i].getPointTwo().getY() * scaleFactor));
		mFacets[i].getPointTwo().setZ((mFacets[i].getPointTwo().getZ() * scaleFactor));

		mFacets[i].getPointThree().setX((mFacets[i].getPointThree().getX() * scaleFactor));
		mFacets[i].getPointThree().setY((mFacets[i].getPointThree().getY() * scaleFactor));
		mFacets[i].getPointThree().setZ((mFacets[i].getPointThree().getZ() * scaleFactor));
	}

	//adjust extents 
	mXMin *= scaleFactor;
	mYMin *= scaleFactor;
	mZMin *= scaleFactor;

	mXMax *= scaleFactor;
	mYMax *= scaleFactor;
	mZMax *= scaleFactor;

	
	return true;
}

bool Model::reduceModel(float reduceFactor){

	return true;
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
	
