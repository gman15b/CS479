#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "image.h"

void readImageHeader(char fname[], int& N, int& M, int& Q, bool& type)
{
 int i, j;
 unsigned char *charImage;
 char header [100], *ptr;
 ifstream ifp;

 ifp.open(fname, ios::in | ios::binary);

 if (!ifp) {
   cout << "Can't read image: " << fname << endl;
   exit(1);
 }

 // read header

 type = false; // PGM

//48 60 255

 ifp.getline(header,100,'\n');
//std::cout << "\n" << header;
 if ( (header[0] == 80) &&  /* 'P' */
      (header[1]== 53) ) {  /* '5' */
      type = false;
 }
 else if ( (header[0] == 80) &&  /* 'P' */
      (header[1] == 54) ) {        /* '6' */
      type = true;
 } 
 else {
   cout << "Image " << fname << " is not PGM or PPM" << endl;
   exit(1);
 }
int numberOffset = 48;

int term1[2] = {header[3]-numberOffset, header[4]-numberOffset};
int term2[2] = {header[6]-numberOffset, header[7]-numberOffset};
int term3[2] = {header[9]-numberOffset, header[10]-numberOffset};
//, header[11]-numberOffset};

 /*M=strtol(header,&ptr,0);
 N=atoi(ptr);

 ifp.getline(header,100,'\n');

 Q=strtol(header,&ptr,0);*/
 M = term1[0] * 10 + term1[1];
 N = term2[0] * 10 + term2[1];
 Q = term3[0] * 100 + term3[1] * 10;// + term3[2];
if (Q > 255)
    Q /= 10;

 ifp.close();

}
