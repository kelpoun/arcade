#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <GL/freeglut.h>
#include "game.h"

void display_callback(); // forward declaration

void reshape_callback(int, int);

void init (){
    glClearColor(0.0, 0.0, 0.0, 1.0); // sets the color of the window, first 3 params are RGB, last param is alpha (keep at 1.0)
    initGrid(40, 40); // function we defined in game.cpp
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // initializes glut, needed to use all glut functions
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE ); // uses RGB and double buffer
    // glutInitWindowPosition(); // optional, sets position on screen, random if not set
    glutInitWindowSize(500, 500); // makes window size 500x500 pixels
    glutCreateWindow("OpenGL 4.3 with Mesa and FreeGLUT"); // creates window with parameter as name
    glutDisplayFunc(display_callback); // displays
    glutReshapeFunc(reshape_callback); // called when window initilaized, and everytime window resized
    init();
    glutMainLoop();
    return 0;
}

void display_callback() {
    glClear(GL_COLOR_BUFFER_BIT); // color buffer will be cleared to value specified by glClearColor
    drawGrid(); // defined in game.cpp
    glutSwapBuffers(); // swap buffer being drawn with buffer being displayed 
}

void reshape_callback(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // sets viewport of window; casts w and h as GLsizei
    glMatrixMode(GL_PROJECTION); // switch to projection mode
    glLoadIdentity(); // reset to identity matrix, specificlaly in projection matrix mode
    glOrtho(0.0, 40.0, 0.0, 40.0, -1.0, 1.0); // look at params, setting coordinate system
    glMatrixMode(GL_MODELVIEW); // go back to model view matrix
}
