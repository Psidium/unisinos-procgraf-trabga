//
//  Loader.cpp
//  JogoGA
//
//  Created by Psidium on 4/11/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "Loader.hpp"

Image* readImage(char* name) {
    std::ifstream arq;
    arq.open(name);
    char type[2];
    char buffer[1024];
    
    arq >> type;
    
    int w,h, maxValue;
    
    // width
    arq >> buffer;
    if (buffer[0] == '#') {
        arq.getline(buffer, 1024);
        arq >> w;
    } else {
        w = atoi(buffer);
    }
    
    //height
    arq >> h;
    
    //cria imagem
    Image* img = new Image(w, h);
    
    arq >> maxValue;
    
    int a,r,g,b;
    
    if (strcmp(type, "P7") == 0){ //texto
        for (int y = h-1; y >= 0; y--) {
            for (int x = 0; x < w; x++){
                arq >> a;
                a = ((float) a/maxValue) * 0xFF;
                arq >> r;
                r = ((float) r/maxValue) * 0xFF;
                arq >> g;
                g = ((float) g/maxValue) * 0xFF;
                arq >> b;
                b = ((float) b/maxValue) * 0xFF;
                int argb = (a << 24) | (r << 16) | (g << 8) | b;
                img->setPixel(argb, x, y);
            }
        }
    } else if (strcmp(type, "P8") == 0) { //binario
        size_t length = w * h * 4 * sizeof(char);
        unsigned char* update = new unsigned char[length+1];
        arq.read((char*) update, (std::streamsize) length+1);
        unsigned char* start_update = update;
        if(arq.eofbit) {
            //file read
            update++;//THIS IS A \N I'M DEAD
            for (int y = h-1; y >= 0; y--) {
                for (int x = 0; x < w; x++){
                    a = (((float) *update)/maxValue) * 0xFF;
                    update++;
                    r = (((float) *update)/maxValue) * 0xFF;
                    update++;
                    g = (((float) *update)/maxValue) * 0xFF;
                    update++;
                    float b1 = (float) *update;
                    b = (b1/maxValue) * 0xFF;
                    update++;
                    int argb = (a << 24) | (r << 16) | (g << 8) | b;
                    img->setPixel(argb, x, y);
                }
            }
        } else {
            std::cerr << "can't read full file";
            exit(7);
        }
        delete[] start_update;
    } else {
        std::cerr << "Corrupt or not found file, buffer is " << type;
        exit(7);
    }
    arq.close();
    
    return img;
}