//
//  ParralaxLayer.cpp
//  JogoGA
//
//  Created by Psidium on 4/24/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "ParallaxLayer.hpp"

ParallaxLayer::ParallaxLayer(Image* action, int portWidth, int portHeight) {
    layers[0] = action;
    viewportSize.height = portHeight;
    viewportSize.width = portWidth;
    curPos.x = 0;
    curPos.y = 0;
}

int ParallaxLayer::addImageWithDistance(Image* img, int distance) {
    //calculate minimum size for that distance and test if the image is that size
    
    //try to insert in the map
    auto ret = layers.insert(std::pair<int,Image*>(distance, img));
    //verify for errors
    if (ret.second==false) {
        //element already exists
        fprintf(stderr, "Element %d already exists!\n", distance);
        return -1;
    }
    return 0;
}

void ParallaxLayer::moveActionLayer(int x, int y) {
    curPos.x += x;
    curPos.y += y;
}

Image* ParallaxLayer::getCurrentBackground() {
    return new Image(1,1);
}
