//
//  Loader.hpp
//  JogoGA
//
//  Created by Psidium on 4/11/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#ifndef Loader_hpp
#define Loader_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Image.hpp"
#include <iostream>

Image* readImage(char* name);
Image* overlap(Image* background, int x, int y, Image* up);


#endif /* Loader_hpp */
