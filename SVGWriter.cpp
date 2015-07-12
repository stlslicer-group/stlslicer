	
#include "SVGWriter.h"
	
//constructor definition

SVGWriter::SVGWriter(std::string fileOutputPath, std::vector<Line>&& lineSegments, WriterParams writerParams) : mFileOutputPath{fileOutputPath}, mLineSegments{std::move(lineSegments)}, mWriterParams{writerParams} {
	//confirm mFileOutputPath is valid
	if (!openFile()){
		throw FileFailedToBeCreatedError{"Could not open file: " + mFileOutputPath +"\n"};
	}

	mHeaderString = ("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" viewBox=\"0 0 " + std::to_string(mWriterParams.getXViewWidth()) + " " + std::to_string(mWriterParams.getYViewWidth()) + "\" preserveAspectRatio=\"xMidYMid meet\">\n\t<title>" + mFileOutputPath + "</title>\n\t<g id=\"slice\">\n");
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
		std::string coords{"\t\t<line x1=\""};
		coords += std::to_string(mLineSegments[i].getPointOne().getY() + mWriterParams.getXTrans());
		coords += "\" y1=\"";
		coords += std::to_string(mLineSegments[i].getPointOne().getZ() + mWriterParams.getYTrans());
		coords += "\" x2=\"";
		coords += std::to_string(mLineSegments[i].getPointTwo().getY() + mWriterParams.getXTrans());
		coords += "\" y2=\"";
		coords += std::to_string(mLineSegments[i].getPointTwo().getZ() + mWriterParams.getYTrans());
		coords += "\"\n"; 
		//TODO make stroke-width a function of point side? User defined?
		coords += "\t\tstroke=\"#999\" stroke-width=\"0.005\" stroke-linecap=\"round\" />\n";
		mFileOut << coords;
/*
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

*/
	}

	mFileOut << ("\t</g>\n</svg>");
}

bool SVGWriter::openFile(){
	mFileOut.open(mFileOutputPath, std::ios_base::out | std::ios_base::trunc);
	if (!mFileOut){
		return false;
	}
	return true;
}
