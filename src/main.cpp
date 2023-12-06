#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "draw.h"
#include <stdlib.h>

// extern global vars
extern bool gameStart;
extern bool gameOver;
extern int snakeDirection;
extern int score;

// forward declarations
void init();
void display_callback();
void reshape_callback(int, int); 
void timer_callback(int);
void keyboard_callback(int key, int, int);
void keyboard_callback2(unsigned char key, int, int);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(500, 500);
    glutCreateWindow("Legless Reptile");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0, timer_callback, 0);
    glutSpecialFunc(keyboard_callback);
    glutKeyboardFunc(keyboard_callback2);
    init();
    glutMainLoop();
    return 0;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.5);
    initGrid(40, 40); // defined in game.cpp; initializes grid to be 40x40
}

void display_callback() {
    glClear(GL_COLOR_BUFFER_BIT); // color buffer will be cleared to value specified by glClearColor

    if (gameStart == 1) {
        drawGameStart();
    }
    else if (!gameOver) {
        // draw functions defined in game.cpp
        drawBoundary();
        drawFood();
        drawNPC(5);
        drawNPC2(25);
        drawNPC3(4);
        drawSnake();
        drawScore();
    }
    else if (gameOver) {
        drawGameOver();
    }

    glutSwapBuffers();
}

void reshape_callback(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 40.0, 0.0, 42.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/10, timer_callback, 0); // FPS set to 10
}

void keyboard_callback(int key, int, int) {
    switch(key) {
        case GLUT_KEY_UP:
            if (snakeDirection != -1){
                snakeDirection = 1;
            } 
            break;
        case GLUT_KEY_DOWN:
            if (snakeDirection != 1){
                snakeDirection = -1;
            } 
            break;
        case GLUT_KEY_RIGHT:
            if (snakeDirection != -2){
                snakeDirection = 2;
            } 
            break;
        case GLUT_KEY_LEFT:
            if (snakeDirection != 2){
                snakeDirection = -2;
            } 
            break;
    }
}

void keyboard_callback2(unsigned char key, int, int) { 
    switch(key) {
        case 27: // escape
            exit(0);
            break;
        case 13: // enter
            if (gameStart) {
                gameStart = 0;
            }
            if (gameOver) {
                reset();
            }
            break;
    }
}
