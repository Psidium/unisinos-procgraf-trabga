//
//  Image.cpp
//  JogoGA
//
//  Created by Psidium on 4/11/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "Image.hpp"

Image::Image(int w, int h) {
    width = w; height = h;
    pixels = (int *) calloc(w*h, sizeof(int));
}

void Image::setPixel(int rgb, int x, int y){
    pixels[x + y*width] = rgb;
}

int Image::getPixel(int x, int y){
    return pixels[x + y*width];
}

Image* Image::copy() {
    Image* cpy = new Image(width, height);
    memcpy(cpy->getPixels(), pixels, width*height * sizeof(int));
    return cpy;
}

void Image::plot(Image* fg, int sx, int sy) {
    float a;
    int r,g,b, pixelUp, pixel;
    for (int y = 0; y < fg->getHeight(); y++) {
        if (y + sy < 0 || y + sy > height) { //protect y outside bounds
            continue;
        }
        for (int x = 0; x < fg->getWidth(); x++){
            if (x + sx < 0 || x + sx > width) {
                continue;
            }
            pixelUp = fg->getPixel(x, y);
            pixel = this->getPixel(x + sx, y + sy);
            a = ((pixelUp >> 24) & 0xFF) / 0xFF;
            if (a == 1.0f) {
                this->setPixel(pixelUp, x + sx, y + sy);
            } else if (a != 0.0f) {
                r = a * ((pixelUp >> 16) & 0xFF) + (1 - a) * ((pixel>> 16) & 0xFF);
                g = a * ((pixelUp >> 8) & 0xFF) + (1 - a) * ((pixel>> 8) & 0xFF);
                b = a * (pixelUp & 0xFF) + (1 - a) * (pixel & 0xFF);
                pixel = (0xFF << 24) | (r << 16) | (g << 8) | b;
                this->setPixel(pixel, x + sx, y + sy);
            }
        }
    }
}

void Image::subimage(Image *dest, int srcX, int srcY) {
    int h = dest->getHeight();
    int w = dest->getWidth();
    for(int y=0; y< h;y++) {
        for (int x=0; x< w; x++) {
            dest->setPixel(this->getPixel(x + srcX, y + srcY), x, y);
        }
    }
}
