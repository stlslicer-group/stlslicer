#include <iostream>
#include <cstdlib>
#include "Model.h"
#include "Error.h"

int main (int argc, char *argv[]){

	/*params:
		int numberOfPlanes
		std::string modelPath
	*/
	
	std::string modelPath = "/home/pas/CppProjects/stlslicer/led.stl";
	
	//Create Model object
	try {
		Model myModel{modelPath};
	} catch (FileFailedToOpenError){
		std::cerr << "Could not open the file.\n";
		return 1;
	}
	//myModel.loadModel();

	
	
	

	
	
	
	return 0;
}
