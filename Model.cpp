	
#include "Model.h"
	
//constructor definition
Model::Model(std::string filePath): mFilePath{filePath} {

}

bool Model::loadModel(){
	//use an STLParser object for this
	mNumberOfFacets = mBinarySTLParser.getNumberOfFacets();
	
	//populate the container
	int i;
	for (i=0; i<mNumberOfFacets; i++){
		mFacets.push_back(mBinarySTLParser.getNextFacet());
	}
	
	std::cout << "All facets loaded; current facet: " << mBinarySTLParser.getNextFacetNumber() << std::endl;

	mFacets[mNumberOfFacets-1].printAllPoints();
	
	mModelLoaded = true;
	return true;	
}


std::string Model::getFilePath() const{
	return mFilePath;
}
	
