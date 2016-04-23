//
//  GameObject.cpp
//  JogoGA
//
//  Created by Psidium on 4/18/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "GameObject.hpp"

GameObject::GameObject(int posX, int posY) {
    this->posX = posX;
    this->posY = posY;
}

void GameObject::incCurrentFrame() {
    this->currentFrame = ++currentFrame % this->animation->getFrameCount();
}

void GameObject::setSprite(Animation* animtion) {
    this->animation = animtion;
}

Image* GameObject::getCurrentFrame() {
    return this->animation->getFrame(this->currentFrame);
}
