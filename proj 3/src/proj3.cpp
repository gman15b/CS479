//Alden Bauman
//Proj 1
//CS 479
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

using namespace std;


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

    //Variables
    int N, M, Q;
    // input images stored as char arrays
    char train1[30] = "00001_930831_fa_a.pgm";
    // output images
    char out1[30] = "Output_1A.pgm";

    ImageType imageBank[4][1205];


    // path for source files
    const char* path = "/home/alden/Desktop/CS479/Proj3/Faces_FA_FB";//"Proj3/Faces_FA_FB";


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

            const char* combinedPath = &combined[0];
            std::cout << combinedPath << endl;
            if ((dir2 = opendir(combinedPath)) != nullptr) {
                while ((fileRead = readdir(dir2)) != nullptr) {
                    if (y >= 0) {
                    std::cout << fileRead->d_name << "| ";
                    char* entry = fileRead->d_name;
                    bool isImage;
                    readImageHeader(entry, N, M, Q, isImage); // read name
                    ImageType inputImg(N, M, Q); // initiate base and test images
                    readImage(entry, inputImg);
                    imageBank[x][y] = inputImg;
                    }

                    y += 1;
                }
            }
            x += 1;

            //            files.push_back(diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");
    }

    for (auto file : files) std::cout << file << "| ";
    std::cout << endl;
    /*for (const auto & imageFolder : std::filesystem::directory_iterator(path)) {
        int y = 0;
        //std::string newDir = path + imageFolder;
        for (const auto & entry : std::filesystem::directory_iterator(path)) {
            //readImageHeader(entry, N, M, Q, isImage); // read name
            //ImageType inputImg(N, M, Q); // initiate base and test images
            //readImage(entry, inputImg);
            //imageBank[x][y] = inputImg;
            y += 1;
        }
        x += 1;
    }*/

    // math variables
    double mean[2], sigma[2][2] = {{0,0}, {0,0}};
    double R, G, bottom, threshR, threshG;
    int counter;

    // read an image in, repeat for each training image
    bool isImage; // checks if image
    //image 1
    //readImageHeader(train1, N, M, Q, isImage); // read name
    //ImageType inputImg(N, M, Q); // initiate base and test images
    //ImageType TestImage(N, M, Q);
    //readImage(train1, inputImg); // read named image into input

    bool trainingMode = true;

    // TRAINING MODE
    // read images, find eigenvectors for average face

    //reconstruction check: recreate images using all eigenvectors to ensure they are calculated correctly

    // TEST MODE


	return 0;
}
