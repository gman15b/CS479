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

Matrix::Matrix(int row, int col){
	cols = col;
	rows = row;
	vector<vector<double>> empty (col, vector<double>(row, 0)); // create empty 2d vector
	copy(empty.begin(), empty.end(), back_inserter(items)); // copy into matrix
}

Matrix::Matrix(int row, int col, vector<vector<double>> input){
	cols = col;
	rows = row;
	try{
	copy(input.begin(), input.end(), back_inserter(items)); // copy into matrix
	}catch(exception e){
		cout << "Error copying matrix items." << endl;
	}
}

Matrix Matrix::getRow(int rowNum) const{ //row num must be valid
	vector<vector<double>> temp; 
	try{
	temp.push_back(items[rowNum]);
	catch(exception e){
		cout << "Invalid rowNum." << endl;
		return;
	}
	return Matrix(1, cols, temp); // return matrix with 1 row, same cols, with values of new row
}

Matrix Matrix::trans(){ // iterate matrix, transpose its items
	vector<vector<double>> transItems;
	for(int i = 0; i < rows; i++){ // iterate 2d vector i.e. matrix
		vector<double> row; // single row
		for(int j = 0; j < cols; j++){
			row.push_back(items[j][i]); // transpose 
		}
		transItems.push_back(row);
	}
	return Matrix(cols, rows, transItems); // return transposed array, swapping cols and rows

}

void Matrix::convertImage(ImageType image){ // iterate matrix, transpose its items
	for(int i = 0; i < rows; i++ ){
		for(int j = 0; j < cols; j++){
			image.getPixel(i, j, items[i][j]);
		}
	}
}

void Matrix::runJacobi(){ // converts matrix to 2d pointer and runs jacobi on it
	double** dblImages = new double*[cols];

	for(int i = 0; i < rows; i++){
		dblImages[i] = new double[i]
		for(int j = 0; j < cols; j++){
			temp[i][j] = images[i][j];
		}
	}

	worked = jacobi(dblImages, rows-1; eigenValues, covMatrix);

}

// average a matrix's eigen values
double Matrix::eigenAvg(){
	double avg = 0;
	if(eigenValues == null){ return avg;}
	for(int i = 0; i < rows; i++){
		avg += eigenValues[i];
	}
	return avg/rows;
}


//////////////////// friend functions //////////////////////////////////////////

// sort eigenvalues of matrix, returning sorted matrix.
// takes in matrix and reference to array.
// note:jacobi takes array doubles for eigen values (w), and 2d doubles / matrix (v) 

Matrix idMatrix(int size){ //return an identity matrix of given dimensions
	Matrix identity = Matrix( size, size)
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(i == j){ identity.items[i][j] = 1; } // set diagonal to 1
		}
	}
	return identity;
}

// this takes in vector of eigenvalues, and matrix of eigenvectors.
pair<double[], Matrix> sortEigen(double[] values, Matrix vectors){
		// iterate values
		int n = sizeof(arr) / sizeof(arr[0]);
		sort(values, values + n); // sort descending
		vector<vector<double>> newVectors (vectors.cols, vector<double>(vectors.rows, 0)); // create empty 2d vector
		int index = 0;
		for(int i = 0; i < newVectors.rows; i++){
			for(int j = 0; j < newVectors.cols; j++){
					if(i == index++){ 
						newVectors[i][j] == values[i];
					}
			}
		}
		return pair<values, newVectors>;
}
