//Alden Bauman
//Proj 1
//CS 479
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "jacobi.h"

int main() {
    int arrSize = 4;
    double testArr[arrSize][arrSize] = {{0,0,0,0}, {0,1,0,0}, {0,2,1,1}, {0,0,0,1}};
    double** testArrPtr = new double*[arrSize];
    double* eigenTest = new double[arrSize];
    double** testArrCov = new double*[arrSize];

    // JACOBI CHECK

    // initialize pointer arrays
    for (int x = 0; x < arrSize; x++) {
        testArrPtr[x] = new double[arrSize];
        testArrCov[x] = new double[arrSize];
    }
    
    // assign values
    for (int x = 0; x < arrSize; x++) {
        for (int y = 0; y < arrSize; y++) {
            testArrPtr[x][y] = testArr[x][y];
        }
    }

    // print array to compare with after
    for (int x = 0; x < arrSize; x++) {
        for (int y = 0; y < arrSize; y++) {
            std::cout << testArrPtr[x][y] << " ";
        }
        std::cout << "\t" << eigenTest[x] << "\t";

        for (int y = 0; y < arrSize; y++) {
            std::cout << testArrCov[x][y] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    jacobi(testArrPtr, arrSize-1, eigenTest, testArrCov);

    for (int x = 0; x < arrSize; x++) {
        for (int y = 0; y < arrSize; y++) {
            std::cout << testArrPtr[x][y] << " ";
        }

        std::cout << "\t" << eigenTest[x] << "\t";

        for (int y = 0; y < arrSize; y++) {
            std::cout << testArrCov[x][y] << " ";
        }
        std::cout << "\n";

    }

    bool trainingMode = true;

    // TRAINING MODE

	return 0;
}
