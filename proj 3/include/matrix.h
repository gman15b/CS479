#pragma once
#include <iostream>

// define what a matrix is for use through/home/gbermeo/Desktop/CS479/proj 3/include/ReadImage.cppout project

using namespace std;

class Matrix {
	public:
	// variables
		int cols;
		int rows;
		vector<vector<double>> items; // items in a row, here 2d array of double for the images
	// constructors	
		Matrix(); // ctor
		Matrix(int row, int col); 
		Matrix(int row, int col, vector<vector<double>> input);
	// functions
		Matrix getRow(int rowNum) const;
		double** convertMatrix();
		double* convertValues();
		Matrix trans(); // transpose matrix items
};
