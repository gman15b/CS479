#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "image.h"

void readImage(char fname[], ImageType& image)
{
 int i, j;
 int N, M, Q;
 unsigned char *charImage;
 char header [100], *ptr;
 ifstream ifp;

 ifp.open(fname, ios::in | ios::binary);

 if (!ifp) {
   cout << "Can't read image: " << fname << endl;
   exit(1);
 }

 // read header

 ifp.getline(header,100,'\n');
 if ( (header[0]!=80) ||    /* 'P' */
      (header[1]!=53) ) {   /* '5' */
      cout << "Image " << fname << " is not PGM" << endl;
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

 charImage = (unsigned char *) new unsigned char [M*N];

 ifp.read( reinterpret_cast<char *>(charImage), (M*N)*sizeof(unsigned char));

 if (ifp.fail()) {
   cout << "Image " << fname << " has wrong size" << endl;
   exit(1);
 }

 ifp.close();

 //
 // Convert the unsigned characters to integers
 //

 int val;

 for(i=0; i<N; i++)
   for(j=0; j<M; j++) {
     val = (int)charImage[i*M+j];
     image.setPixelVal(i, j, val);     
   }

 delete [] charImage;

}
