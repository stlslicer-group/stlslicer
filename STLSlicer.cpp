#include <iostream>
#include <cstdlib>
#include "Model.h"

int main (int argc, char *argv[]){

	/*params:
		int numberOfPlanes
		string modelPath
	*/
	
	std::string modelPath = "/home/pas/CppProjects/stlslicer/led.stl";
	
	//Create Model object
	
	Model myModel{modelPath};
	myModel.loadModel();

	
	
	

	
	
	
	return 0;
}
