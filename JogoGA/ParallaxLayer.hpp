//
//  ParralaxLayer.hpp
//  JogoGA
//
//  Created by Psidium on 4/24/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef ParallaxLayer_hpp
#define ParallaxLayer_hpp

#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <map>
#include "Image.hpp"
#include "GameObject.hpp"

class ParallaxLayer {
public:
    ParallaxLayer(Image* action, int viewportSizeX, int viewportSizeY);
    int addImageWithDistance(Image* img, int distance);
    void moveActionLayer(int x, int y);
    Image* getCurrentBackground();
private:
    std::map<int, Image*> layers;
    
    struct Position {
        int x;
        int y;
    } curPos;
    
    struct ImageSize {
        int width;
        int height;
    } viewportSize;
};
#endif /* ParralaxLayer_hpp */
