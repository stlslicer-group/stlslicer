#include <iostream>
#include <cstdlib>
#include "Model.h"
#include "ThreeDPoint.h"


void printExtents(const std::vector<ThreeDPoint>&);


int main (int argc, char *argv[]){

	/*params:
		int numberOfSlices
		std::string modelPath
		std::string folderOutputPath
	*/
	
	int numberOfSlices = 20; 
	std::string modelPath = "/home/pas/CppProjects/stlslicer/led.stl";
	std::string folderOutputPath = "/home/pas/CppProjects/stlslicer/";
	
	//Create Model object
	
	Model myModel{modelPath};
	
	//load the data into the model object
	if (!myModel.loadModel()){
		std::cerr << "The data could not be loaded into the model.\n";
		return 1;
	}
	
	//print extents
	std::vector<ThreeDPoint> extents{myModel.getExtents()};
	printExtents(extents);

	myModel.slice(numberOfSlices, folderOutputPath);


	return 0;
}

void printExtents(const std::vector<ThreeDPoint>& extents){
	std::cout << "Min Coords: \n X: " << extents[0].getX() << " Y: " << extents[0].getY() << " Z: " << extents[0].getZ() << "\n";
	std::cout << "Max Coords: \n X: " << extents[1].getX() << " Y: " << extents[1].getY() << " Z: " << extents[1].getZ() << "\n";
}
