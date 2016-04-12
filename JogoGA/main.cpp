//
//  main.cpp
//  JogoGA
//
//  Created by Psidium on 4/11/16.
//  Copyright © 2016 Psidium. All rights reserved.
//

#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <math.h>
#include <fstream>
#include <stdio.h>
#include "Image.hpp"
#include "Loader.hpp"

unsigned char kb;

Image* img;

void init(void)
{
    /*  select clearing (background) color       */
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    img = readImage("braveText.ptm");
    
    /*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}


void reshape(int width, int height){
    glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y){
    kb = key;
}



void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glDrawPixels(img->getWidth(), img->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE,img->getPixels());
    
    glFlush();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("hello");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}