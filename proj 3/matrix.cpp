#include "matrix.h"

using namespace std;
/*
// define what a matrix is for use throughout project



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
}
*/

Matrix::Matrix(int row, int col){
	columns = col;
	rows = row;
	vector<vector<double>> empty (col, vector<double>(row, 0)); // create empty 2d vector
	copy(empty.begin(), empty.end(), back_inserter(items)); // copy into matrix
}

Matrix::Matrix(int row, int col, vector<vector<double>> input){
	columns = col;
	rows = row;
	try{
	copy(input.begin(), input.end(), back_inserter(items)); // copy into matrix
	}catch(Error e){
		cout << "Error copying matrix items." << endl;
	}
}


Matrix::printMatrix(){
	for(int i = 0; i < items.size(); i++){
		for(int j = 0; j < items[i].size(); j++){
			
		}
	}





}
