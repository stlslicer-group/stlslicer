#ifndef FILE_Model_SEEN
#define FILE_Model_SEEN

#include <string>
#include <vector>
#include <limits>
#include "STLParser.h"
#include "Facet.h"
//#include "Slicer.h"
#include "Error.h"

class Model {
	private:
		//private members
		std::string mFilePath;		
		bool mModelLoaded{false};
		int mNumberOfFacets{0};
		std::vector<Facet> mFacets{}; 
		float mXMax{std::numeric_limits<float>::lowest()};
		float mYMax{std::numeric_limits<float>::lowest()};
		float mZMax{std::numeric_limits<float>::lowest()};
		float mXMin{std::numeric_limits<float>::max()};
		float mYMin{std::numeric_limits<float>::max()};
		float mZMin{std::numeric_limits<float>::max()};

		//private functions
		void checkExtents(const Facet& currentFacet);
		void checkMaxMin(const ThreeDPoint& currentPoint);
		void resetModel();
	
	public:
		//constructor
		Model(std::string filePath);

		bool loadModel();
		bool reloadModel();

		//TODO incorrect results in two functions below
		bool scaleModel(float scaleFactor);
		bool reduceModel(float reduceFactor);

		std::string getFilePath() const;
		bool isModelLoaded() const;

		//min then max
		std::vector<ThreeDPoint> getExtents() const;

		bool slice(int numberOfSlices, std::string outputPath);	

		//declare Slicer a friend class so that it may access the Facet vector
		friend class Slicer;
};

#endif

