	
#include "SVGWriter.h"
	
//constructor definition

SVGWriter::SVGWriter(std::string fileOutputPath, std::vector<Line>&& lineSegments, int yMax, int zMax) : mFileOutputPath{fileOutputPath}, mYMax{yMax}, mZMax{zMax}, mLineSegments{std::move(lineSegments)} {
	//confirm mFileOutputPath is valid
	if (!openFile()){
		throw FileFailedToBeCreatedError{"Could not open file: " + mFileOutputPath +"\n"};
	}
	
	mHeaderString = ("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n<svg\nversion=\"1.1\"\nwidth=\"" + std::to_string(mYMax) + "\"\nheight=\"" + std::to_string(mZMax) +"\"\nid=\"svg2\">\n<defs\nid=\"defs4\" />\n");
}

SVGWriter::~SVGWriter(){
	//release the file
	mFileOut.close();
}

void SVGWriter::write(){
	
	mFileOut << mHeaderString;
	
	//write the path
		//form a string that looks like "M x,y x,y x,y x,y z"
	unsigned int i;
	for(i = 0; i < mLineSegments.size(); i++){
		std::string coords{"d=\"M "};
		mFileOut << "<path\nstyle=\"fill:none;stroke:#000000;stroke-width:3px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"";
		
		coords+=std::to_string(mLineSegments[i].getPointOne().getY());
		coords+=",";
		coords+=std::to_string(mLineSegments[i].getPointOne().getZ());
		coords+=" ";
		coords+=std::to_string(mLineSegments[i].getPointTwo().getY());
		coords+=",";
		coords+=std::to_string(mLineSegments[i].getPointTwo().getZ());
		coords+="\"\nid=\"path"+std::to_string(i)+"\"\n/>";
		mFileOut << "\n"+ coords +"\n";
	}

	mFileOut << ("</svg>");
}

bool SVGWriter::openFile(){
	mFileOut.open(mFileOutputPath, std::ios_base::out | std::ios_base::trunc);
	if (!mFileOut){
		return false;
	}
	return true;
}
