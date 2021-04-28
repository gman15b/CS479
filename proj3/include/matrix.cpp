#include "matrix.h"
#include <cmath>
#include <algorithm>
#include <iomanip>

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

//////////////////// friend functions //////////////////////////////////////////

// sort eigenvalues of matrix, returning sorted matrix.
// takes in matrix and reference to array.
// note:jacobi takes array doubles for eigen values (w), and 2d doubles / matrix (v) 
double* runJacobi(ImageType image, int rows, int cols){ // converts matrix to 2d pointer and runs jacobi on it
    double** dblImages = new double*[cols];
    double** covMatrix = new double*[cols];
    double* eigenValues = new double[cols];

    for(int i = 0; i < cols; i++){
	    dblImages[i] = new double[rows];
        covMatrix[i] = new double[rows];
	    for(int j = 0; j < rows; j++){
            int tempPixel;
		    image.getPixelVal(i,j, tempPixel);
            dblImages[i][j] = (double)tempPixel;
        }
    }

    jacobi(dblImages, rows-1, eigenValues, covMatrix);
    return eigenValues;

}

// average a matrix's eigen values
double eigenAvg(double* eigenValues, int size){
	double avg = 0;
	for(int i = 0; i < size; i++){
		avg += eigenValues[i];
	}	
	return (double)avg/size;
}

Matrix idMatrix(int size){ //return an identity matrix of given dimensions
	Matrix identity = Matrix( size, size);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(i == j){ identity.images[i][j] = 1; } // set diagonal to 1
		}
	}
	return identity;
}


bool sortbysecdesc(const pair<int,double> &a, const pair<int,double> &b){
       return a.second>b.second;
} // helper for next function


// this takes in eigenBank of sorted eigen values. Returns sorted, averaged eigen bank.
double** sortEigen(double** eigenBank, int size, int cols){
		vector< pair <int, double>> averages; // original place, avg
		for (int i = 0; i < size; i++){
			double avg = eigenAvg(eigenBank[i], cols);
			averages.push_back(make_pair(i , avg)); // adds pair of original place and its avg
		}
		sort(averages.begin(), averages.end(), sortbysecdesc);
		double** sortedBank = new double*[size];
		for(int i = 0; i < size; i++){
			sortedBank[i] = eigenBank[averages[i].first];
			cout << averages[i].second << endl;
		}
		return sortedBank;
}
