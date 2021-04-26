#ifndef IMAGE_H
#define IMAGE_H

#include "rgb.h" // for more complex images

// a simple example - you would need to add more functions

class ImageType {
 public:
   ImageType();
   ImageType(int, int, int);
   void getImageInfo(int&, int&, int&);
   void setImageInfo(int, int, int);
   void setPixelVal(int, int, RGB);
   void getPixelVal(int, int, RGB&);
 private:
   int N, M, Q;
   RGB **pixelValue;
};

#endif
