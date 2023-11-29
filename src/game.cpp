#include <GL/gl.h>
#include <GL/freeglut.h>
#include "game.h"

int gridX, gridY;

void initGrid(int x, int y) {
    gridX = x;
    gridY = y;
}

void unit(int, int); // forward declaration
void drawGrid() {
    unit(20,20);
}

void unit(int x, int y) { // draw one unit
    glLineWidth(1.0); // optional (because default already 1.0), width of line
    glColor3f(1.0, 1.0, 1.0); // optional (because default already white), color of line

    glBegin(GL_LINE_LOOP); // GL_LINE_LOOP is geometric primitive, loop means shape is closed
    glVertex2f(x, y); // draws line to vertex
    glVertex2f(x + 1, y); // draws line to vertex
    glVertex2f(x + 1, y + 1); // draws line to vertex
    glVertex2f(x, y + 1); // draws line to vertex
    glEnd(); // end drawing stuff
}