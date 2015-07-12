	
#include "WriterParams.h"
	
//constructor definition
WriterParams::WriterParams(int xViewWidth, int yViewWidth, float xTrans, float yTrans) : mXViewWidth{xViewWidth}, mYViewWidth{yViewWidth}, mXTrans{xTrans}, mYTrans{yTrans} {
	
}
	

int WriterParams::getXViewWidth() const {
	return mXViewWidth;
}

int WriterParams::getYViewWidth() const {
	return mYViewWidth;
}

float WriterParams::getXTrans() const {
	return mXTrans;
}

float WriterParams::getYTrans() const {
	return mYTrans;
}
