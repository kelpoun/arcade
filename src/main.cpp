#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <GL/freeglut.h>
#include "game.h"
#include <stdlib.h>

extern int sDirection;
bool gameOver = false;
int score = 0;

// forward declarations
void timer_callback(int);
void display_callback(); 
void reshape_callback(int, int);
void keyboard_callback(int, int, int); // first param = ASCI value of key pressed, other params is position of mouse

void init (){
    glClearColor(0.0, 0.0, 0.0, 0.5); // sets the color of the window, first 3 params are RGB, last param is alpha (keep at 1.0)
    initGrid(40, 40); // function we defined in game.cpp
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // initializes glut, needed to use all glut functions
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE ); // uses RGB and double buffer
    // glutInitWindowPosition(); // optional, sets position on screen, random if not set
    glutInitWindowSize(500, 500); // makes window size 500x500 pixels
    glutCreateWindow("Legless Reptile"); // creates window with parameter as name
    glutDisplayFunc(display_callback); // displays
    glutReshapeFunc(reshape_callback); // called when window initilaized, and everytime window resized
    glutTimerFunc(0, timer_callback, 0); // called starts at 0 ms (first param)
    glutSpecialFunc(keyboard_callback); // calls anytime a special key is pressed (arrows)
    init();
    glutMainLoop(); // detects 
    return 0;
}

void display_callback() {
    glClear(GL_COLOR_BUFFER_BIT); // color buffer will be cleared to value specified by glClearColor
    drawGrid(); // defined in game.cpp
    drawSnake();
    drawFood();
    drawNPC(5);
    drawNPC(30);
    drawNPC(25);
    drawNPC2(4);
    glutSwapBuffers(); // swap buffer being drawn with buffer being displayed 
    if (gameOver) {
        char _score[10]; // array of score (will prob not exceed 10 chars)
        // itoa(score, _score, 10); // integer value to characters in #include <stdlib.h>; IDK what last param is; doesn't work?
        // char text[50] = "Your score: "; // doesn't work?
        // strcat (text, _score); // doesn't work?
        // MessageBox(NULL, "Your Score : ",  "GAME OVER", 0); // only for windows, doesn't work? 
        exit(0);
    }
}

void reshape_callback(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // sets viewport of window; casts w and h as GLsizei
    glMatrixMode(GL_PROJECTION); // switch to projection mode
    glLoadIdentity(); // reset to identity matrix, specificlaly in projection matrix mode
    glOrtho(0.0, 40.0, 0.0, 40.0, -1.0, 1.0); // look at params, setting coordinate system
    glMatrixMode(GL_MODELVIEW); // go back to model view matrix
}

void timer_callback(int) {
    glutPostRedisplay(); // urges program to redisplay
    glutTimerFunc(1000/10, timer_callback, 0); // calls every 1000/10 times per second
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