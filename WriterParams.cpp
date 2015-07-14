	
#include "WriterParams.h"
	
//constructor definition
WriterParams::WriterParams(int zViewHeight, int yViewWidth, float yTrans, float zTrans) : mZViewHeight{zViewHeight}, mYViewWidth{yViewWidth}, mYTrans{yTrans}, mZTrans{zTrans} {
	
}
	

int WriterParams::getZViewHeight() const {
	return mZViewHeight;
}

int WriterParams::getYViewWidth() const {
	return mYViewWidth;
}

float WriterParams::getYTrans() const {
	return mYTrans;
}

float WriterParams::getZTrans() const {
	return mZTrans;
}
