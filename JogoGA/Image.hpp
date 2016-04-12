//
//  Image.hpp
//  JogoGA
//
//  Created by Psidium on 4/11/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include <stdio.h>



class Image {
public:
    Image(int w, int h){
        width = w; height = h;
        pixels = new int[w*h];
    }
    void setPixel(int rgb, int x, int y){
        pixels[x + y*width] = rgb;
    }
    int getPixel(int x, int y){
        return pixels[x + y*width];
    }
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    
    int* getPixels(){
        return pixels;
    }
    ~Image() {
        delete pixels;
    }
    
private:
    int *pixels; // alternativamente char *pixels ñ 1 byte por canal
    // neste caso, pixels = new char[w*h*3];
    int width, height;
};



#endif /* Image_hpp */
