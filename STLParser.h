#ifndef FILE_STLParser_SEEN
#define FILE_STLParser_SEEN

#include "Facet.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdint> //for fixed width integers
#include <vector>
#include "Error.h"

class STLParser {
	private:
		//private members
		std::string mFilePath;
		uint32_t mNumberOfFacets{0};
		uint32_t mNextFacetNumber{1};
		bool mFileOpen{false};
		bool mBigEndian{true};
		std::ifstream mInFile{};

		//private methods
		bool openFile();
		void endianCheck();
		uint32_t readUnsignedInt();
		float readFloat();
	
	public:
		//constructor
		STLParser(std::string filePath);

		//destructor
		~STLParser();

		//disallow copying and assignments
		STLParser(const STLParser& stlParser) = delete;
		STLParser& operator=(const STLParser& stlParser) = delete;


		Facet getNextFacet();
		
		//should only be called after first getNextFacet(), or else zero returned
		uint32_t getNumberOfFacets() const;
		//range of [1, getNumberOfFacets()]
		uint32_t getNextFacetNumber() const;

		//TODO reset/rewind function
		
};

#endif


