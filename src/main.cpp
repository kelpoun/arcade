#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <GL/freeglut.h>
#include "draw.h"
#include <stdlib.h>

// extern global vars
extern int sDirection;
extern int score;
extern bool gameOver;

// forward declarations
void init();
void display_callback();
void reshape_callback(int, int); 
void timer_callback(int);
void keyboard_callback(int key, int, int);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(500, 500);
    glutCreateWindow("Legless Reptile");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0, timer_callback, 0);
    glutSpecialFunc(keyboard_callback);
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

    // draw functions defined in game.cpp
    drawBoundary();
    drawSnake();
    drawFood();
    drawNPC(5);
    drawNPC2(25);
    drawNPC3(4);

    glutSwapBuffers();
    if (gameOver) {
        exit(0);
    }
}

void reshape_callback(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 40.0, 0.0, 40.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/10, timer_callback, 0); // FPS set to 10
}

void keyboard_callback(int key, int, int) {
    switch(key) {
        case GLUT_KEY_UP:
            if (sDirection != -1){
                sDirection = 1;
            } 
            break;
        case GLUT_KEY_DOWN:
            if (sDirection != 1){
                sDirection = -1;
            } 
            break;
        case GLUT_KEY_RIGHT:
            if (sDirection != -2){
                sDirection = 2;
            } 
            break;
        case GLUT_KEY_LEFT:
            if (sDirection != 2){
                sDirection = -2;
            } 
            break;
    }
}