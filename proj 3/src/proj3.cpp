/*
Project 3
CS 479
Gabriel Bermeo & Alden Bauman
*/
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <time.h>

//#include <filesystem>
#include <dirent.h>
#include <string>
#include <vector>

#include "jacobi.cpp"
#include "ReadImage.cpp"
#include "ReadImageHeader.cpp"
#include "WriteImage.cpp"
#include "image.cpp"
#include "cstring"

#include <unistd.h>

using namespace std;

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

int main() {
// Part 1 testing for known eigenvalues.
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
///////////////////////////////////////////////////////////////////////
// Part 2, reading in images for use.
//////////////////////////////////////////////////////////////////////
    //Variables
    int N, M, Q;
    // input images stored as char arrays
    char train1[30] = "00001_930831_fa_a.pgm";
    // output images
    char out1[30] = "Output_1A.pgm";

    ImageType imageBank[4][605]; // 1205
    int imageToParse = 150;


    // path for source files 
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    char path[100];
    char images[30] = "/Faces_FA_FB";
    strcpy(path,cwd);
    strcat(path,images);
    
    // marks down dimensions of images
    int highX = 48;
    int highY = 60;
    int lowX = 16;
    int lowY = 20;



    DIR *dir; 
    DIR *dir2; 
    struct dirent *dirRead;
    struct dirent *fileRead;
    std::vector<char *> files;

    // iterates through all files in directory and stores their contents
    if ((dir = opendir(path)) != nullptr) {
        int x = 0;
        while ((dirRead = readdir(dir)) != nullptr) {
            int y = -2; // starts at -2 to prevent noise in image files
            string extension = dirRead->d_name;
            string base = path;
            string combined = base + "/" + extension;
            bool exitLoop = false;

            if (extension[0] != '.' && x < 4) {
                const char* combinedPath = &combined[0];
                //std::cout << combinedPath << endl << x << endl;
                if ((dir2 = opendir(combinedPath)) != nullptr) {
                    while ((fileRead = readdir(dir2)) != nullptr && !exitLoop) {
                        string extension2 = fileRead->d_name;
                        string imageLoc = combined + "/" + extension2;
                        char* imageLocChar = &imageLoc[0];
                        //std::cout << imageLoc << endl;
                        // imports image at imageLocChar location
                        if (y >= 0) {
                            char* entry = imageLocChar;
                            bool isImage;
                            readImageHeader(entry, N, M, Q, isImage); // read name
                            ImageType inputImg(N, M, Q); // initiate base and test images
                            readImage(entry, inputImg);
                            imageBank[x][y] = inputImg;
                        }

                        y += 1;
                        if (y > imageToParse)
                            exitLoop = true;
                    }
                }
            }
            else
                x -= 1;
            x += 1;

            //            files.push_back(diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");
    }
    



    // size of rows and columns for this set of images
    int cols = lowY;
    int rows = lowX;

    //holds eigenvectors for set of faces
    double** eigenBank = new double*[cols];

    // collects eigeenvalues for all faces, stores them in eigenBank
    for (int x = 0; x < imageToParse; x++) {
        eigenBank[x] = runJacobi(imageBank[0][x], rows, cols);
    }



    /*Matrix matrixBank[4][1205];

    for (int x = 0; x < imageToParse; x++) {
        Matrix* m = new Matrix(highX, highY);
        matrixBank[0][x] = *m;
        matrixBank[0][x].convertImage(imageBank[0][x]);
        matrixBank[0][x].runJacobi();
    }*/

    // math variables
    double mean[2], sigma[2][2] = {{0,0}, {0,0}};
    double R, G, bottom, threshR, threshG;
    int counter;


    bool trainingMode = true;

    // TRAINING MODE
    // read images, find eigenvectors for average face

    //reconstruction check: recreate images using all eigenvectors to ensure they are calculated correctly

    // TEST MODE


	return 0;
}
