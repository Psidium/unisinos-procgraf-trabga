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
    }
    else {
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
                arq >> r;
                arq >> g;
                arq >> b;
                int argb = (a << 24) | (r << 16) | (g << 8) | b;
                img->setPixel(argb, x, y);
            }
        }
    }
    else if (strcmp(type, "P8") == 0) { //binario
        arq.read(buffer, 1024);
    } else {
        std::cerr << "Corrupt or not found file, buffer is " << type;
        exit(7);
    }
    arq.close();
    
    return img;
}