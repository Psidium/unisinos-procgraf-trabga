//
//  ImageSpin.hpp
//  JogoGA
//
//  Created by Psidium on 4/22/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef ImageSpin_hpp
#define ImageSpin_hpp

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Image.hpp"

class ImageSpin: private Image {
public:
    ImageSpin* spinWithRad(float rad);
};

#endif /* ImageSpin_hpp */
