#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <GL/freeglut.h>
#include "game2.h"

void display_callback();
void reshape_callback(int, int);
void timer_callback(int);
void keyboard_callback(int key, int, int);

void init (){
    glClearColor(0.0, 0.0, 0.0, 1.0); // sets the color of the window, first 3 params are RGB, last param is alpha (keep at 1.0)
    // initialize background
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1080, 1080);
    glutCreateWindow("Legless Reptile");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0, timer_callback, 0);
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();
    
    return 0;
}

void display_callback() {
    glClear(GL_COLOR_BUFFER_BIT);
    // add moveable player, NPCs, background, etc.
    glutSwapBuffers();
}

void reshape_callback(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 40.0, 0.0, 40.0, -1.0, 1.0); // coordinate system set from 40x40
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/10, timer_callback, 0); // 10 FPS (update every 100 ms)
}

void keyboard_callback(int key, int, int) {
    switch(key) {
        case GLUT_KEY_UP:
            // move logic
            break;
        case GLUT_KEY_DOWN:
            // move logic
            break;
        case GLUT_KEY_RIGHT:
            // move logic
            break;
        case GLUT_KEY_LEFT:
            // move logic
            break;
    }
}