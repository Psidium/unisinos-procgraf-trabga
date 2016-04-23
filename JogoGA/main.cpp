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
#include "GameObject.hpp"
#include "Animation.hpp"
#include "ImageSpin.hpp"

#define BACK_COUNT 22

unsigned char kb;

Image* scene;
GameObject* background;
Image* front;

void init(void)
{
    /*  select clearing (background) color       */
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    
    //create animation
    Animation* animation = new Animation(BACK_COUNT);
    for (int i = 1; i <= BACK_COUNT; i++) {
        char filename[30];
        sprintf(filename, "back1_%d..ptm", i);
        Image* img = readImage(filename);
        animation->addFrame(img);
    }
    
    background = new GameObject(0,0);
    background->setSprite(animation);
    
    front = readImage("Grass.ptm");
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
    
    glDrawPixels(scene->getWidth(), scene->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE,scene->getPixels());
    
    glFlush();
}

void update(int value){
    //destroy last image
    if (scene != NULL) {
        scene->~Image();
    }
    
    background->incCurrentFrame();
    scene = background->getCurrentFrame()->copy();
    
    
    if(front != NULL) {
        Image holder = Image(1024, 200);
        front->subimage(&holder, 0, front->getHeight() - holder.getHeight());
        scene->plot(&holder, 0, 0);
    }
    
    glutPostRedisplay(); // para rederizar quadro "atual"
    glutTimerFunc(60, update, value);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("hello");
    init();
    update(0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}