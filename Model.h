#ifndef FILE_Model_SEEN
#define FILE_Model_SEEN

#include <string>
#include <vector>
#include "STLParser.h"
#include "Facet.h"
//#include "Error.h"

class Model {
	private:
		//private members
		std::string mFilePath;		
		bool mModelLoaded{false};
		STLParser mBinarySTLParser{mFilePath};
		int mNumberOfFacets{0};
		std::vector<Facet> mFacets{}; 
	
	public:
		//constructor
		Model(std::string filePath);

		bool loadModel();
		std::string getFilePath() const;
};

#endif

