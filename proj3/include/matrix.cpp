#include "matrix.h"

using namespace std;
/*
// define what a matrix is for use throughout project



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
	Matrix getRow(int row) const;
	Matrix trans(); // transpose matrix items
}
*/
Matrix::Matrix(){
	cols = 4;
	rows = 4;
	vector<vector<double>> empty (cols, vector<double>(rows, 0)); // create empty 2d vector
	copy(empty.begin(), empty.end(), back_inserter(images)); // copy into matrix
}


Matrix::Matrix(int row, int col){
	cols = col;
	rows = row;
	vector<vector<double>> empty (cols, vector<double>(rows, 0)); // create empty 2d vector
	copy(empty.begin(), empty.end(), back_inserter(images)); // copy into matrix
}

Matrix::Matrix(int row, int col, vector<vector<double>> input){
	cols = col;
	rows = row;
	try{
	copy(input.begin(), input.end(), back_inserter(images)); // copy into matrix
	}catch(exception e){
		cout << "Error copying matrix items." << endl;
	}
}

Matrix Matrix::getRow(int rowNum) const{ //row num must be valid
	vector<vector<double>> temp; 
	try{
	temp.push_back(images[rowNum]);
	}catch(exception e){
		cout << "Invalid rowNum." << endl;
		exit(1);
	}
	return Matrix(1, cols, temp); // return matrix with 1 row, same cols, with values of new row
}

Matrix Matrix::trans(){ // iterate matrix, transpose its items
	vector<vector<double>> transImages;
	for(int i = 0; i < rows; i++){ // iterate 2d vector i.e. matrix
		vector<double> row; // single row
		for(int j = 0; j < cols; j++){
			row.push_back(images[j][i]); // transpose 
		}
		transImages.push_back(row);
	}
	return Matrix(cols, rows, transImages); // return transposed array, swapping cols and rows

}

void Matrix::convertImage(ImageType image){ // iterate matrix, transpose its items
	int val = 0;
	for(int i = 0; i < rows; ++i ){
		for(int j = 0; j < cols; ++j){
			image.getPixelVal(i, j, val);
			images[i][j] = val;
		}
	}
}
/*
double* Matrix::runJacobiInternal(){ // converts matrix to 2d pointer and runs jacobi on it
	double** dblImages = new double*[cols];
	int tempPixel = 0;
	// convert matrix to 2d double
	for(int i = 0; i < rows; i++){
		dblImages[i] = new double[cols];
        covMatrix[i] = new double[cols];
		for(int j = 0; j < cols; j++){
		    image.getPixelVal(i,j, tempPixel);
			dblImages[i][j] = (double)tempPixel;
		}
	}
	// run jacobi on it
	jacobi(dblImages, rows-1, eigenValues covMatrix);
	return eigenValues;
}
*/

