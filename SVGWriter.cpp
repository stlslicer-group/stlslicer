	
#include "SVGWriter.h"
	
//constructor definition

SVGWriter::SVGWriter(std::string fileOutputPath, std::vector<Line>&& lineSegments, WriterParams writerParams) : mFileOutputPath{fileOutputPath}, mLineSegments{std::move(lineSegments)}, mWriterParams{writerParams} {
	//confirm mFileOutputPath is valid
	if (!openFile()){
		throw FileFailedToBeCreatedError{"Could not open file: " + mFileOutputPath +"\n"};
	}

	mHeaderString = ("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"20cm\" height=\"20cm\" viewBox=\"0 0 " + std::to_string(mWriterParams.getYViewWidth()) + " " + std::to_string(mWriterParams.getZViewHeight()) + "\" preserveAspectRatio=\"xMidYMid meet\">\n\t<title>" + mFileOutputPath + "</title>\n\t<g id=\"slice\">\n");
//TODO comeup with a better <g> group id which includes the slice number
}

/*std::to_string(mWriterParams.getZViewWidth())*/ 
/*std::to_string(mWriterParams.getYViewHeight())*/
SVGWriter::~SVGWriter(){
	//release the file
	mFileOut.close();
}

void SVGWriter::write(){
	
	mFileOut << mHeaderString;
	
	//SVG uses a left hand coord system; have to switch x and y to retain the orientation of the model

	unsigned int i;
	for(i = 0; i < mLineSegments.size(); i++){
		
		//1) move the points to the positive quad
		//	do this by adding mWriterParams.getYTrans() to Y points and mWriterParams.getZTrans() to Z points
		//2) rotate the points 270 deg through (Y,Z) -> (Z, -Y)
		//	(y1, z1) -> (z1, -y1) (y2, z2) -> (z2, -y2)
		//3) translate back to positive quad by adding max Y to Z
		//	(y1, z1) -> (y1, z1 + initialWidth)

		std::string coords{"\t\t<line x1=\""};

		auto finalY1 = mLineSegments[i].getPointOne().getZ() + mWriterParams.getZTrans();
		auto finalZ1 = (-(mLineSegments[i].getPointOne().getY() + mWriterParams.getYTrans())) + mWriterParams.getZViewHeight();
		auto finalY2 = mLineSegments[i].getPointTwo().getZ() + mWriterParams.getZTrans();
		auto finalZ2 = (-(mLineSegments[i].getPointTwo().getY() + mWriterParams.getYTrans())) + mWriterParams.getZViewHeight();

		coords += std::to_string(finalY1); 
		coords += "\" y1=\"";
		coords += std::to_string(finalZ1);
		coords += "\" x2=\"";
		coords += std::to_string(finalY2);
		coords += "\" y2=\"";
		coords += std::to_string(finalZ2);
		coords += "\"\n"; 
		//TODO make stroke-width a function of area? User defined? //0.005 for led
		coords += "\t\tstroke=\"#999\" stroke-width=\"1\" stroke-linecap=\"round\" />\n";
		mFileOut << coords;
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
