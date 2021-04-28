#pragma once
#include <iostream>
#include <vector>
#include "image.h"

// define what a matrix is for use throught

using namespace std;

class Matrix {
	public:
	// variables
		int cols;
		int rows;
		int worked;
		vector<vector<double>> images; // items in a row, here 2d array of double for the images
	// constructors	
		Matrix(); // ctor
		Matrix(int row, int col); 
		Matrix(int row, int col, vector<vector<double>> input);
	// functions
		Matrix getRow(int rowNum) const;
		Matrix trans(); // transpose matrix items
		void convertImage(ImageType image); // convert 1 image into 2d vector for images
	
		// friends
		friend double eigenAvg(double* eigenValues, int size);
		friend double* runJacobi(ImageType image, int rows, int cols);
		friend Matrix idMatrix(int size);
		friend double** sortEigen(double** eigenValues, int size, int cols);
};
