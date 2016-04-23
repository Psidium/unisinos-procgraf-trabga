//
//  GameObject.hpp
//  JogoGA
//
//  Created by Psidium on 4/18/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include "Animation.hpp"
#include "Image.hpp"

class GameObject {
public:
    GameObject(int posX, int posY);
    void incCurrentFrame();
    void setSprite(Animation* animtion);
    Image* getCurrentFrame();
private:
    int currentFrame;
    int posX;
    int posY;
    Animation* animation;
};
#endif /* GameObject_hpp */
