//
//  Animation.cpp
//  JogoGA
//
//  Created by Psidium on 4/18/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include "Animation.hpp"

Animation::Animation(int frameCount){
    this->frameCount = frameCount;
}

void Animation::addFrame(Image* frame) {
    this->frames.push_back(frame);
}

Image* Animation::getFrame(int frame) {
    return this->frames.at(frame);
}

int Animation::getFrameCount() {
    return this->frameCount;
}

Animation::~Animation() {
    //c++11 "for-each"-like
    for (auto &image: this->frames) {
        delete image;
    }
    this->frames.clear();
}