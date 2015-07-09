#ifndef FILE_SVGWriter_SEEN
#define FILE_SVGWriter_SEEN

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Line.h"
#include "Error.h"

class SVGWriter {
	private:
		//private members
		std::string mFileOutputPath;
		std::ofstream mFileOut{};
		int mXMax;
		int mYMax;
		//line segments
		const std::vector<Line> mLineSegments;
		std::string mHeaderString{};

		//private functions
		bool openFile();

	
	public:
		//constructor
		SVGWriter(std::string fileOutputPath, std::vector<Line>&& lineSegments, int xMax, int yMax);

		//destructor
		~SVGWriter();

		//disallow copying and assignments
		SVGWriter(const SVGWriter& svgWriter) = delete;
		SVGWriter& operator=(const SVGWriter& svgWriter) = delete;
		
		//public functions
		void write();

};

#endif

