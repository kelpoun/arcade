#include <GL/gl.h>
#include <GL/freeglut.h>
#include <iostream>
#include "game.h"

bool upArrow = false;
bool downArrow = false;
bool rightArrow = false;
bool leftArrow = false;

float posX = 20;
float posY = 20;
float xVelocity = 0;
float yVelocity = 0;

void drawPlayer() {
    if (upArrow == false && downArrow == false && rightArrow == false && leftArrow == false) {
        xVelocity *= 0.8;
        yVelocity *= 0.8;
    }
    if (upArrow == true) {
        yVelocity += 0.2;
    }
    if (downArrow == true) {
        yVelocity -= 0.2;
    }
    if (rightArrow == true) {
        xVelocity += 0.2;
    }
    if (leftArrow == true) {
        xVelocity -= 0.2;
    }
    posX += xVelocity;
    posY += yVelocity;
    glColor3f(1.0, 0.0, 0.0);
    glRectd(posX, posY, posX + 1, posY + 1);
}