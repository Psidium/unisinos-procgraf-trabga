//
//  ImageSpin.cpp
//  JogoGA
//
//  Created by Psidium on 4/22/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "ImageSpin.hpp"

ImageSpin* ImageSpin::spinWithRad(float rad) {
    int w = this->getWidth();
    int h = this->getHeight();
    ImageSpin* out = (ImageSpin*) new Image(w, h + (h * rad));
    //debug style
    for (int x=0; x<w; x++) {
        for (int y=0; y<h;y++) {
            int argb = this->getPixel(x, y);
            int newX = x - tanf(rad/2) * y;
            out->setPixel(argb, newX, y);
        }
    }
    for (int x=0; x<w; x++) {
        for (int y=0; y<h;y++) {
            int argb = out->getPixel(x, y);
            int newY = sinf(rad) * x + y;
            out->setPixel(argb, x, newY);
        }
    }
    for (int x=0; x<w; x++) {
        for (int y=0; y<h;y++) {
            int argb = out->getPixel(x, y);
            int newX = x - tanf(rad/2) * y;
            out->setPixel(argb, newX, y);
        }
    }
    return out;
    
}