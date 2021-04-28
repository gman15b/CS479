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
#include <unistd.h>
#include <dirent.h>
#include "cstring"
#include <vector>

#include "jacobi.cpp"
#include "ReadImage.cpp"
#include "ReadImageHeader.cpp"
#include "WriteImage.cpp"
#include "image.cpp"
#include "eigen.cpp"


// marks down dimensions of images
/*
static int highX = 48;
static int highY = 60;
static int lowX = 16;
static int lowY = 20;
*/
static int rows = 48;
static int cols = 60;
static int imageToParse = 1196; //600


using namespace std;

// returns test image difference from closest eigenvector
double testImage(double** eigenBank, ImageType sampleImage, int numImages) {
    // eigen info for test image
    double* testEigen = runJacobi(sampleImage, rows, cols);
    double minDistance = 99999.0;
    double tempDistance, currentDistance;

    /*for (int i = 1; i < rows; i++)
        std::cout << testEigen[i] << " ";
    std::cout << "\n\n";
    for (int h = 0; h < 5; h++) {
        for (int i = 1; i < rows; i++)
            std::cout << eigenBank[h][i] << " ";
        std::cout << "\n\n";
    }*/

    // finds the distance to the closest eigenvector
    for (int x = 0; x < numImages; x++) {
        currentDistance = 0.0;
        for (int y = 1; y < rows; y++) {
            tempDistance = testEigen[y] - eigenBank[x][y];
            //gets absolute value of distance
            if (tempDistance < 0.0)
                tempDistance *= -1;
            currentDistance += tempDistance;
        }
        if (currentDistance < minDistance)
            minDistance = currentDistance;
    }
    return minDistance;
    
}

int main() {
// Part 1 testing for known eigenvalues.
    int arrSize = 4;
    double testArr[arrSize][arrSize] = {{0,0,0,0}, {0,1,0,0}, {0,2,1,1}, {0,0,0,1}};
    double** testArrPtr = new double*[arrSize];
    double* eigenTest = new double[arrSize];
    double** testArrCov = new double*[arrSize];

    // JACOBI CHECK
    bool checkJacobi = false;
    if (checkJacobi) {
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
    }
///////////////////////////////////////////////////////////////////////
// Part 2, reading in images for use. Training.
// // TRAINING MODE
// // read images, find eigenvectors for average face
//////////////////////////////////////////////////////////////////////
    //Variables
    int N, M, Q;

    // number of images to read from each directory
    ImageType gallery[1205]; // 1205
    ImageType query[1196];
    ImageType queryB[1196];
    // path for source files 
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    char path[100];
    char images[30] = "/Faces_FA_FB";
    strcpy(path,cwd);
    strcat(path,images);
    

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

            if (extension[0] != '.') { // read in 2 galleries
                const char* combinedPath = &combined[0];
                //std::cout << combinedPath << endl << x << endl;
                if ((dir2 = opendir(combinedPath)) != nullptr) {
                    //cout << combinedPath << endl;
                    while ((fileRead = readdir(dir2)) != nullptr && !exitLoop) {
                        string extension2 = fileRead->d_name;
                        string imageLoc = combined + "/" + extension2;
                        char* imageLocChar = &imageLoc[0];
                        //std::cout << imageLoc << endl;
                        // imports image at imageLocChar location
                        if (y >= 0 && x == 1) {
                            char* entry = imageLocChar;
                            bool isImage;
                            readImageHeader(entry, N, M, Q, isImage); // read name
                            ImageType inputImg(N, M, Q); // initiate base and test images
                            readImage(entry, inputImg);
                            gallery[y] = inputImg;
                        }else if (y >= 0 && x == 3) {
                            char* entry = imageLocChar;
                            bool isImage;
                            readImageHeader(entry, N, M, Q, isImage); // read name
                            ImageType inputImg(N, M, Q); // initiate base and test images
                            readImage(entry, inputImg);
                            query[y] = inputImg;
                        }else if (y >= 0 && x == 4) {
                            char* entry = imageLocChar;
                            bool isImage;
                            readImageHeader(entry, N, M, Q, isImage); // read name
                            ImageType inputImg(N, M, Q); // initiate base and test images
                            readImage(entry, inputImg);
                            queryB[y] = inputImg;
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

    ImageType meanFace(cols, rows, 250);
    int currentVal, tempVal;

    // calculate mean face for set 1
    for (int y = 0; y < cols; y++){
        for (int z = 0; z < rows; z++){
            for (int x = 0; x < imageToParse; x++){
                // adds pixel to mean pixel
                meanFace.getPixelVal(y,z, currentVal);
                gallery[x].getPixelVal(y,z, tempVal);
                meanFace.setPixelVal(y,z, currentVal+tempVal);
            }
            meanFace.getPixelVal(y,z, currentVal);
            meanFace.setPixelVal(y,z, currentVal/imageToParse);
            meanFace.getPixelVal(y,z, currentVal);
            //std::cout << currentVal << " ";
        }
        //std::cout << std::endl;
    }

    // subtract mean face from each image
    for (int y = 0; y < cols; y++){
        for (int z = 0; z < rows; z++){
            for (int x = 0; x < imageToParse; x++){
                // adds pixel to mean pixel
                meanFace.getPixelVal(y,z, currentVal);
                gallery[x].getPixelVal(y,z, tempVal);
                gallery[x].setPixelVal(y,z, tempVal-currentVal);
            }
        }
    }

    //holds eigenvectors for set of faces
    double** eigenBank = new double*[cols];
    // make covariance matrix
    double** covMatrix = new double*[cols]; 
    double combinedEigen[cols];
    double totalEigen = 0.0; // holds total of eigen vals to normalize

    // collects eigeenvalues for all faces, stores them in eigenBank
    for (int x = 0; x < imageToParse; x++) {
        eigenBank[x] = runJacobi(gallery[x], rows, cols);
    }

    //prints out all eigenvalues
    /*for (int x = 1; x < imageToParse; x++) {
        for (int y = 1; y < rows; y++) {
            std::cout << " " << eigenBank[x][y];
        }
        std::cout << "\n";
    }*/

    //makes combined eigenvector and normalizes it
    for (int x = 1; x < rows; x++) {
        combinedEigen[x] = 0.0;
        for (int y = 1; y < imageToParse; y++) {
            combinedEigen[x] += eigenBank[y][x];
            //std::cout << " " << eigenBank[x][y];
            totalEigen += eigenBank[y][x];
        }
        combinedEigen[x] /= (imageToParse - 1);
        //std::cout << "\n";
        //std::cout << combinedEigen[x] << " ";
    }
    totalEigen /= (imageToParse - 1);
    double minEigen = -9999.0;
    double maxEigen = 9999.0;
    int tempPixel;

    // attempted eigenface creation
    ImageType im1 = meanFace;
    ImageType eigenFaces[1196]; // array of eigenfaces?
    for (int i = 1; i < imageToParse; i++) {
        ImageType outputImage(cols, rows, 250);
        // applys eigenvectors to each pixel
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                int currentPixel;
                double eigenPixel = 0;
                im1.getPixelVal(y, x, currentPixel);
                //eigenPixel = currentPixel * combinedEigen[y] / totalEigen;

                //keeps track of max and min eigenvalues so results can be normalized
                minEigen = 9999.0;
                maxEigen = -9999.0;
                //meanFace.getPixelVal(y,x, tempPixel);
                gallery[i].getPixelVal(y,x, tempPixel);

                for (int pic = 1; pic < rows; pic++) {
                    int pixelVal = eigenBank[i][pic];
                    eigenPixel += pixelVal;
                    if (pixelVal > maxEigen)
                        maxEigen = pixelVal;
                    if (pixelVal < minEigen)
                        minEigen = pixelVal;
                }
                eigenPixel /= rows;
                eigenPixel -= tempPixel;
                int normalizedPixel = (int)255*(eigenPixel-minEigen)/(maxEigen-minEigen);

                outputImage.setPixelVal(y,x,normalizedPixel);
                if (i == -1)
                    std::cout << normalizedPixel << " ";
            }
            if (i == -1)
                std::cout << "\n";
            //im1.getPixelVal(y, x, currentPixel);
            //std::cout << " " << currentPixel;
        }
        eigenFaces[i] = outputImage;
    }



    //}*/

///////////////////////////////////////////////////////////////////////
// // TEST MODE
// // compare images to eigenface to see if they are close enough
//////////////////////////////////////////////////////////////////////

    // runs testImage on one of the training images to ensure it is working properly
    double memberDistance = testImage(eigenBank, gallery[3], imageToParse);
    double threshold = 100.0;
    if (memberDistance < threshold)
        std::cout << "Face detected\n";
    else
        std::cout << "Face not detected\n";

    std::cout << "Minimum Distance: " << memberDistance << "\n";


////////////////////////////////////////////////////////////////////////
// Part 3, experiments.
///////////////////////////////////////////////////////////////////////
// 3a.1 show mean face, then 10 largest and smallest eigenvalue faces
    writeImage("experiment/3a1-mean.pgm", meanFace); // mean face

    // sort eigenfaces  
    vector<pair<int, double>> sortedKey = sortEigen(eigenBank, imageToParse, cols); 
    for(int i = 0; i < 10; i++){ // for 10 images
        // creates output filename
        char tmp1[] = "experiment/10Top";
        char tmp2[] = ".pgm";
        char * outputLoc = new char[30];
        std::strcpy(outputLoc,tmp1);
        std::strcat(outputLoc,to_string(i).c_str());
        std::strcat(outputLoc,tmp2);

        // outputs test eigenface
        writeImage(outputLoc, eigenFaces[sortedKey[i].first]);
        double memberDistance = testImage(eigenBank, eigenFaces[sortedKey[i].first], imageToParse);
        cout << "Image " << i+1 << "'s distance:" << memberDistance << endl;
        delete[] outputLoc;
    }
    for(int i = sortedKey.size()-10; i < sortedKey.size(); i++){ // for 10 images
        // creates output filename
        char tmp1[] = "experiment/10Bottom";
        char tmp2[] = ".pgm";
        char * outputLoc = new char[30];
        std::strcpy(outputLoc,tmp1);
        std::strcat(outputLoc,to_string(i).c_str());
        std::strcat(outputLoc,tmp2);

        // outputs test eigenface
        //writeImage(outputLoc, gallery[sortedKey[i].first]);
        writeImage(outputLoc, eigenFaces[sortedKey[i].first]);
        delete[] outputLoc;
    }
// 3a.2 distance
////////////////////// 80%
    for (int i = 0; i < 20; i++){
        char tmp1[] = "match/80%GalleryMatch";
        char tmp2[] = ".pgm";
        char * outputLoc = new char[30];
        std::strcpy(outputLoc,tmp1);
        std::strcat(outputLoc,to_string(i).c_str());
        std::strcat(outputLoc,tmp2);
        writeImage(outputLoc, gallery[sortedKey[i].first]);
        delete[] outputLoc;
    }
    for (int i = 0; i < 20; i++){
        char tmp1[] = "match/80%QueryMatch";
        char tmp2[] = ".pgm";
        char * outputLoc = new char[30];
        std::strcpy(outputLoc,tmp1);
        std::strcat(outputLoc,to_string(i).c_str());
        std::strcat(outputLoc,tmp2);
        writeImage(outputLoc, query[sortedKey[i].first]);
        delete[] outputLoc;
    }
/////////////////////////// 90 / 95%
       for (int i = 0; i < 20; i++){
        char tmp1[] = "match/80%GalleryMatch";
        char tmp2[] = ".pgm";
        char * outputLoc = new char[30];
        std::strcpy(outputLoc,tmp1);
        std::strcat(outputLoc,to_string(i).c_str());
        std::strcat(outputLoc,tmp2);
        writeImage(outputLoc, gallery[sortedKey[i].first]);
        delete[] outputLoc;
    }
    for (int i = 0; i < 20; i++){
        char tmp1[] = "match/80%QueryMatch";
        char tmp2[] = ".pgm";
        char * outputLoc = new char[30];
        std::strcpy(outputLoc,tmp1);
        std::strcat(outputLoc,to_string(i).c_str());
        std::strcat(outputLoc,tmp2);
        writeImage(outputLoc, query[sortedKey[i].first]);
        delete[] outputLoc;
    }


    return 0;
}

