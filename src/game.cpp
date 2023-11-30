#include <GL/gl.h>
#include <GL/freeglut.h>
#include "game.h"
#include <ctime>

int gridX, gridY;
int snake_length = 5;
bool food = true;
int foodX, foodY;
int sDirection = 2; // stores curr direction of snake; default right; 1 up, -1 down, 2 right, -2 left; note can be "short" type
extern bool gameOver;
int posX[60] = {20, 20, 20, 20, 20}, posY[60] = {20, 19, 18, 17, 16}; // we are using square grid, so we don't need floating points; array that can hold 60 positions (max length of snake)
extern int score;

bool right = true; //direction for npc

void initGrid(int x, int y) {
    gridX = x;
    gridY = y;
}

void unit(int, int); // forward declaration
void drawGrid() {
    for (int x = 0; x < gridX; x++) { // makes a grid at every x, y
        for (int y = 0; y < gridY; y++) {
            unit(x,y);
        }
    }
}

void unit(int x, int y) { // draw one unit
    if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1) { // outer boundaries
        glLineWidth(3.0);
        glColor3f(1.0, 0.0, 0.0);
        glRectd(x,y, x+1, y+1);
    }
    else {
        /* glLineWidth(1.0); // optional (because default already 1.0), width of line
        glColor3f(1.0, 1.0, 1.0); // optional (because default already white), color of line
        glBegin(GL_LINE_LOOP); // GL_LINE_LOOP is geometric primitive, loop means shape is closed
        glVertex2f(x, y); // draws line to vertex
        glVertex2f(x + 1, y); // draws line to vertex
        glVertex2f(x + 1, y + 1); // draws line to vertex
        glVertex2f(x, y + 1); // draws line to vertex
        glEnd (); */// end drawing stuff
    }
}

void drawFood() {
    if (food) {
        random(foodX, foodY); // if food is true, randomize food position
    }
    food = false; // reset food
    glColor3f(1.0, 1.0, 0.0);
    glRectf(foodX, foodY, foodX + 1, foodY + 1); // draw food
}


int i = 1;
int npcX1 = i;
int npcX2 = i;
int npcX3 = i; 
void drawNPC( int j) {
    glColor3f(1.0, 0.0, 0.0);
    glRectd(i, j, i+1, j+1);
    if (i > 37) {
        right = false;
    }
    if (right) {
    i++;
    npcX1++;
    npcX2++;
    npcX3++;
    }

    else {
        i--;
        npcX1--;
        npcX2--;
        npcX3--;
        if (i < 2) {
            right = true;
        }
    }
}

bool up = true;

int j = 1;
void drawNPC2 (int i ) {
    glColor3f(1.0, 0.0, 0.0);
    glRectd(i, j, i+1, j+1);
    if (j > 37) {
        up = false;
    }
    if (up) {
    j++;
    npcX1++;
    npcX2++;
    npcX3++;
    }

    else {
        j--;
        npcX1--;
        npcX2--;
        npcX3--;
        if (j < 2) {
            up = true;
        }
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

    for(int i = 1;i < snake_length; i++) { // ends game if head hits part of snake
        if(posX[i] == posX[0] && posY[i] == posY[0]) {
            gameOver=true;
        }    
    }
    
    
    if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1) { // check if snake has been in red area
        gameOver = true;
    }
    if (posX[0] == foodX && posY[0] == foodY) { // if head reaches food
        score++;
        if (snake_length > 60) { // prevents snake from growing greater than 60
            snake_length = 60;
        }

        food = true;
    }
}



void random (int &x, int &y) {
    int _maxX = gridX - 2; // max value is 38
    int _maxY = gridY - 2; // max value is 38
    int _minX = 1;
    int _minY = 1;

    srand(time(NULL)); // makes sure random place isn't same
    x = _minX + rand() % (_maxX - _minX); // algorithm to get random number between 1 and 38 (inclusive)
    y = _minY + rand() % (_maxY - _minY);
}