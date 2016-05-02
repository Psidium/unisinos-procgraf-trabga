//
//  Image.hpp
//  JogoGA
//
//  Created by Psidium on 4/11/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



class Image {
public:
    Image(int w, int h);
    void setPixel(int rgb, int x, int y);
    int getPixel(int x, int y);
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    int* getPixels(){ return pixels; }
    void plot(Image* fg, int sx, int sy);
    void subimage(Image *dest, int srcX, int srcY);
    
    ~Image() { delete pixels; }
    Image* copy();
    
private:
    int *pixels; // alternativamente char *pixels ñ 1 byte por canal
    // neste caso, pixels = new char[w*h*3];
    int width, height;
};




#endif /* Image_hpp */
