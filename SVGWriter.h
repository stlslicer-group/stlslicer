#ifndef FILE_SVGWriter_SEEN
#define FILE_SVGWriter_SEEN

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Line.h"
#include "WriterParams.h"
#include "Error.h"

class SVGWriter {
	private:
		//private members
		std::string mFileOutputPath;
		std::ofstream mFileOut{};

		//line segments
		const std::vector<Line> mLineSegments;
		std::string mHeaderString{};

		//writer params
		WriterParams mWriterParams;

		//private functions
		bool openFile();

	
	public:
		//constructor
		SVGWriter(std::string fileOutputPath, std::vector<Line>&& lineSegments, WriterParams writerParams);

		//destructor
		~SVGWriter();

		//disallow copying and assignments
		SVGWriter(const SVGWriter& svgWriter) = delete;
		SVGWriter& operator=(const SVGWriter& svgWriter) = delete;
		
		//public functions
		void write();

};

#endif

