#include "matrix.h"
#include "jacobi.h"
#include <cmath>
#include <algorithm>
#include <iomanip>
//////////////////// friend functions //////////////////////////////////////////

// sort eigenvalues of matrix, returning sorted matrix.
// takes in matrix and reference to array.
// note:jacobi takes array doubles for eigen values (w), and 2d doubles / matrix (v) 
double* runJacobi(ImageType image, int rows, int cols){ 
    // takes in image of a size, makes into 2d matrix, runs jacobi on it
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

/*
Matrix idMatrix(int size){ //return an identity matrix of given dimensions
	Matrix identity = Matrix( size, size);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(i == j){ identity.images[i][j] = 1; } // set diagonal to 1
		}
	}
	return identity;
}
*/

bool sortbysecdesc(const pair<int,double> &a, const pair<int,double> &b){
       return a.second>b.second;
} // helper for next function


// this takes in eigenBank of sorted eigen values. Returns legend of sorted values.
vector<pair<int, double>> sortEigen(double** eigenBank, int size, int cols){
		vector< pair <int, double>> averages; // original place, avg
		for (int i = 0; i < size; i++){
			double avg = eigenAvg(eigenBank[i], cols);
			averages.push_back(make_pair(i , avg)); // adds pair of original place and its avg
		}
		sort(averages.begin(), averages.end(), sortbysecdesc);
		/*
		double** sortedBank = new double*[size];
		for(int i = 0; i < size; i++){
			sortedBank[i] = eigenBank[averages[i].first];
			//cout << averages[i].second << endl;
		}
		return sortedBank;
		*/
	return averages;
}
