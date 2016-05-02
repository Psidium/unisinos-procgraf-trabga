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

#define GAME_CONSTANT_MOTION 10
#define VIEWPORT_X 1000
#define VIEWPORT_Y 750

Image* scene;
Image* background;
Image* ground;
Image* front;
Image* arvore;
Image* montanha;
GameObject* andaDireita;
GameObject* andaEsquerda;

bool andandoParaEsquerda = false;
bool andandoParaDireita = false;
bool isJumping = false;

int x = 200, y = 0;

void init(void)
{
    /*  select clearing (background) color       */
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    
    //create animation
  /*  Animation* animation = new Animation(BACK_COUNT);
    for (int i = 1; i <= BACK_COUNT; i++) {
        char filename[30];
        sprintf(filename, "back1_%d..ptm", i);
        Image* img = readImage(filename);
        animation->addFrame(img);
    }*/
    
    
    background = readImage("FundoPaisagem.ptm");
    //cut to fit the viewport
    Image* nBack = new Image(VIEWPORT_X, VIEWPORT_Y);
    nBack->plot(background, 0,0);
    background->~Image();
    background = nBack;
    
    
    Image* sprite = readImage("SpriteSheet2_s.ptm");
    
    Animation* walkForward = new Animation(3);
    Image* img = new Image(100,189);
    sprite->subimage(img,0,0);
    walkForward->addFrame(img);
    
    Image* img2 = new Image(104,189);
    sprite->subimage(img2,100,0);
    walkForward->addFrame(img2);
    
    Image* img3 = new Image(108,189);
    sprite->subimage(img3,204,0);
    walkForward->addFrame(img3);
    
    Animation* walkBackwards = new Animation(3);
    Image* img_ = new Image(100,189);
    sprite->subimage(img_,0,189);
    walkBackwards->addFrame(img_);
    
    Image* img_2 = new Image(104,189);
    sprite->subimage(img_2,100,189);
    walkBackwards->addFrame(img_2);
    
    Image* img_3 = new Image(108,189);
    sprite->subimage(img_3,204,189);
    walkBackwards->addFrame(img_3);
    
    andaEsquerda = new GameObject(0,0);
    andaEsquerda->setSprite(walkForward);
    
    andaDireita = new GameObject(300,0);
    andaDireita->setSprite(walkBackwards);
    
    sprite->~Image();
    
    
    ground = readImage("Chao.ptm");
    
    montanha = readImage("FundoMontanhas.ptm");
    
    arvore = readImage("Arvore1.ptm");
    
    /*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}


void reshape(int width, int height){
    glutReshapeWindow(VIEWPORT_X, VIEWPORT_Y);
}

void keyboard(unsigned char key, int x, int y){
}

void calcVerticalVector(bool start) {
    static int currentTime = 0;
    //protect the jump
    if (start && isJumping){
        return;
    } else
    ///handle start of jumping
    if (start && !isJumping) {
        isJumping = true;
        currentTime = 0;
    }
    y = ground->getHeight() + 100 * currentTime + (-30 * pow(currentTime,2)) / 2;
    currentTime++;
    if (y < ground->getHeight()) {
        isJumping = false;
        return;
    }
}

void specialInput(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            calcVerticalVector(true);
            break;
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
            andandoParaEsquerda = true;
            break;
        case GLUT_KEY_RIGHT:
            andandoParaDireita = true;
            break;
    }
}


void specialUp(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
            andandoParaEsquerda = false;
            break;
        case GLUT_KEY_RIGHT:
            andandoParaDireita = false;
            break;
    }
    
}

void contro() {
    static int wx = 0;
    wx += GAME_CONSTANT_MOTION/2;
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glDrawPixels(scene->getWidth(), scene->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE,scene->getPixels());
    
    glFlush();
}

void update(int value) {
    static Image* lastFrame;
    
    //don't recalculate everything if nothing is changed
    static int ox =0, oy=0;
    //if old x is equal to current x and old y is equal to current y and isn't walingRight neither Left neither jumping
    if (ox == x && oy == y && !andandoParaDireita && !andandoParaEsquerda && !isJumping) {
        //postpone calculation for next frame
        glutTimerFunc(60, update, value);
        return;
    } else {
        ox = x;
        oy = y;
    }
    //destroy last image
    if (scene != NULL) {
        scene->~Image();
    }
    scene = background->copy();
    
    if (isJumping) {
        calcVerticalVector(false);
    }
    if (y < ground->getHeight()) {
        y=ground->getHeight();
    }
    
    //control the bicho on top of the ground
    if (andandoParaEsquerda) {
        x -= GAME_CONSTANT_MOTION;
        andaEsquerda->incCurrentFrame();
        lastFrame = andaEsquerda->getCurrentFrame();
    } else if (andandoParaDireita) {
        x += GAME_CONSTANT_MOTION;
        andaDireita->incCurrentFrame();
        lastFrame = andaDireita->getCurrentFrame();
    } else if (lastFrame == NULL) {
        lastFrame = andaDireita->getCurrentFrame();
    }
    //limit bicho's walking possibilities
    if (x < 0) x = 0;
    if (x + lastFrame->getWidth() > ground->getWidth()) x = ground->getWidth() - lastFrame->getWidth();
    
    
    Image actionLayer = Image(ground->getWidth(), VIEWPORT_Y);
    actionLayer.plot(ground, 0, 0);
    actionLayer.plot(lastFrame, x, y);
    
    int parX =0, parY =0;
    if (x > VIEWPORT_X/3) {
        parX = VIEWPORT_X/3 - x;
        if (abs(parX) + VIEWPORT_X > actionLayer.getWidth()) {
            parX = VIEWPORT_X - actionLayer.getWidth();
        }
    }
    scene->plot(montanha, parX/2 * VIEWPORT_X/montanha->getWidth(),0);
    scene->plot(&actionLayer, parX, parY);
    scene->plot(arvore, parX * VIEWPORT_X/arvore->getWidth() + VIEWPORT_X*3/4, 0);
    glutPostRedisplay(); // para rederizar quadro "atual"
    glutTimerFunc(60, update, value);
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(VIEWPORT_X, VIEWPORT_Y);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("hello");
    init();
    update(0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialInput);
    glutSpecialUpFunc(specialUp);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}