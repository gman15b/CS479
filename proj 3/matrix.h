#pragma once
#include <vector>
#include <iostream>


// define what a matrix is for use throughout project

using namespace std;

class Matrix {
	public:
	// variables
		int columns;
		int rows;
		vector<vector<double>> items; // items in a row, here 2d array of double for the images
	// constructors	
		Matrix(); // ctor
		Matrix(int row, int col); 
		Matrix(int row, int col, vector<vector<double>> input);
	// functions
	Matrix getRow(int row) const;
	friend Matrix product(const Matrix& a, const Matrix& b);
};
