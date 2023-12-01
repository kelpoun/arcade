#include <GL/gl.h>
#include <GL/freeglut.h>
#include "draw.h"
#include <ctime>

// extern global vars
int sDirection = 2; // snake direction: 1 = up, -1 = down, 2 = right, -2 = left
int score = 0;
bool gameOver = 0;

// grid logic
int gridX, gridY;

// snake logic
int snake_length = 5;
int posX[5] = {20, 20, 20, 20, 20}, posY[60] = {20, 19, 18, 17, 16}; // array of snake's position; max length 60

// food logic
bool food = true; // if true food needs to be drawn in random pos
int foodX, foodY;

// npc logic
bool right1 = true; // direction for npc1
bool right2 = true; // direction for npc2
bool up = true; // direction for npc3

void initGrid(int x, int y) {
    gridX = x;
    gridY = y;
}

void unit(int x, int y) { // draw one unit
    if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1) { // outer boundaries
        glLineWidth(3.0);
        glColor3f(1.0, 0.0, 0.0);
        glRectd(x, y, x + 1, y + 1);
    }
}

void drawBoundary() {
    for (int x = 0; x < gridX; x++) {
        unit(x, 0);
        unit(x, gridY - 1);
    }
    for (int y = 1; y < gridY - 1; y++) {
        unit(0, y);
        unit(gridX - 1, y);
    }
}

void random (int &x, int &y) { // helper function drawFood(); randomoizes food location
    int minX = 1;
    int minY = 1;
    int maxX = gridX - 2; // max value is 38
    int maxY = gridY - 2; // max value is 38

    srand(time(NULL)); // changes seed of rand()
    x = minX + rand() % (maxX - minX); // algorithm to get random number between 1 and 38 (inclusive)
    y = minY + rand() % (maxY - minY);
}

void drawFood() {
    if (food) {
        random(foodX, foodY); // if food is true, randomize food position
        food = false; // reset food
    }
    glColor3f(1.0, 1.0, 0.0); 
    glRectf(foodX, foodY, foodX + 1, foodY + 1);
}

int npc1_X = 5; // x start position of npc1
void drawNPC(int npc1_Y) {
    glColor3f(1.0, 0.0, 0.0);
    glRectd(npc1_X, npc1_Y, npc1_X + 1, npc1_Y + 1 );
    if (npc1_X < 2) {
        right1 = true;
    }
    if (npc1_X > 37) {
        right1 = false;
    }
    if (right1) {
        npc1_X++;
    }
    else {
        npc1_X--;
    }
}

int npc2_X = 1; // x start position of npc2
void drawNPC2(int npc2_Y) {
    glColor3f(1.0, 0.0, 0.0);
    glRectd(npc2_X, npc2_Y, npc2_X + 1, npc2_Y + 1 );
    if (npc2_X < 2) {
        right2 = true;
    }
    if (npc2_X > 37) {
        right2 = false;
    }
    if (right2) {
        npc2_X++;
    }
    else {
        npc2_X--;
    }
}

int npc3_Y = 1; // y start position of npc3
void drawNPC3(int npc3_X) {
    glColor3f(1.0, 0.0, 0.0);
    glRectd(npc3_X, npc3_Y, npc3_X + 1, npc3_Y + 1 );
    if (npc3_Y < 2) {
        up = true;
    }
    if (npc3_Y > 37) {
        up = false;
    }
    if (right2) {
        npc3_Y++;
    }
    else {
        npc3_Y--;
    }
}

void drawSnake() {
    for (int i = snake_length - 1; i > 0; i--) { // previous snake block switched; note head a index 0
        posX[i] = posX[i - 1];
        posY[i] = posY[i - 1];
    }
    if (sDirection == 1) {
        posY[0]++;
    }
    else if (sDirection == -1) {
        posY[0]--;
    }
    else if (sDirection == 2) {
        posX[0]++;
    }
    else if (sDirection == -2) {
        posX[0]--;
    }
    for (int i = 0; i < snake_length; i++) {
        if (i == 0 ) { // head will be green
            glColor3f(0.0, 1.0, 0.0); 
        }
        else { // non head will be blue
            glColor3f(0.0, 0.0, 1.0); 
        }
        glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
    }
    glColor3f(0.0, 1.0, 0.0);

    for(int i = 1;i < snake_length; i++) { // ends game if head hits npc
        if(posX[i] == npc1_X && posY[i] == 5 ) {
            gameOver =true;
        }

        else if(posX[i] == npc2_X && posY[i] == 25 ) {
            gameOver =true;
        } 

        else if(posX[i] == 4 && posY[i] == npc3_Y ) {
            gameOver =true;
        }
    }
    
    if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1) { // check if snake has been in red area
        gameOver = true;
    }
    if (posX[0] == foodX && posY[0] == foodY) { // if head reaches food
        score++;
        food = true;
    }
}