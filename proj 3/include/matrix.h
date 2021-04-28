#pragma once
#include <iostream>
#include <vector>
#include "image.h"

// define what a matrix is for use through/home/gbermeo/Desktop/CS479/proj 3/include/ReadImage.cppout project

using namespace std;

class Matrix {
	public:
	// variables
		int cols;
		int rows;
		int worked;
		vector<vector<double>> images; // items in a row, here 2d array of double for the images
		
		double* eigenValues;
		double** covMatrix;
		
	// constructors	
		Matrix(); // ctor
		Matrix(int row, int col); 
		Matrix(int row, int col, vector<vector<double>> input);
	// functions
		Matrix getRow(int rowNum) const;
		Matrix trans(); // transpose matrix items
		void convertImage(ImageType image); // convert 1 image into 2d vector for images
		void runJacobi();
		double eigenAvg();
		
		// friends
		friend Matrix idMatrix(int size);
		void sortEigen();
};
