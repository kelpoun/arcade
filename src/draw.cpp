#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "draw.h"
#include <random>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <string.h>
#include <vector>

// extern global vars
bool gameStart = 1;
bool gameOver = 0;
int snakeDirection = 2; // snake direction: 1 = up, -1 = down, 2 = right, -2 = left
int score = 0;

// grid logic
int gridX, gridY;

// game snake logic
int snakeLength = 5;
int posX[5] = {20, 20, 20, 20, 20}, posY[5] = {20, 19, 18, 17, 16}; // array of snake's position; max length 60

// display screen snake logic
int startSnakeLength = 5;
int startPosX[5] = {15, 14, 13, 12, 11}, startPosY[5] = {11, 11, 11, 11, 11}; // array of snake's position; max length 60
int startDirection = 2;

// food logic
bool food = true; // if true food needs to be drawn in random pos
int foodX, foodY;

// npc logic
bool right1 = true; // direction for npc1
bool right2 = true; // direction for npc2
bool up = true; // direction for npc3
bool upDown = true; // direction for npc3
bool upDown2 = true; // direction for npc2
int count = 8;
int count2 = 10;

// npc snakes logic
int npc4_length =  1;
int npc3Direction = -1;
int npc2_length = 1;
int npc2Direction = 1;



// text display logic
int startFlash = 0;
int endFlash = 0;
std::vector<int> scores; // all scores
std::vector<int> highestScores; // top 5 scores

void initGrid(int x, int y) {
    gridX = x;
    gridY = y;
}

void unit(int x, int y) { // draw one unit
    glLineWidth(3.0);
    glColor3f(1.0, 0.0, 0.0);
    glRectd(x, y, x + 1, y + 1);
}

void drawBoundary() {
    for (int x = 0; x < gridX; x++) {
        unit(x, 0);
        unit(x, gridY - 2);
    }
    for (int y = 1; y < gridY - 2; y++) {
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

void randomDirection() {
    std::mt19937 rng(static_cast<unsigned>(std::time(0)));

    int ydirections[] = {-1,1};
    int xdirections[] = {-2,2};

    std::uniform_int_distribution<int> distribution(0,1);
    int randomIndex = distribution(rng);

    if (upDown) {
        npc3Direction = xdirections[randomIndex]; 

        upDown = false;
    }

    else {
        npc3Direction = ydirections[randomIndex]; 
        upDown = true;
    }

    
    
}

void randomDirection2() {
    std::mt19937 rng(static_cast<unsigned>(std::time(0)));

    int y2directions[] = {-1,1};
    int x2directions[] = {-2,2};

    std::uniform_int_distribution<int> distribution2(0,1);
    int randomIndex = distribution2(rng);

    if (upDown2) {
        npc2Direction = x2directions[randomIndex]; 

        upDown2 = false;
    }

    else {
        npc2Direction = y2directions[randomIndex]; 
        upDown2 = true;
    }

    
    
}



int npc1_Y = 3;
int npc1_X = 5;
void drawNPC(int npc1_Y) {
    if (score <= 5) {
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

        if (score == 5) {
            npc1_X = 0;
        }
    }
}

int npc2_X = 1; // x start position of npc2
int lastY2;
int n2posX[30] = {0};  
int n2posY[30] = {20};
void drawNPC2(int npc2_Y) {
    if (score <= 5) {
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

        if (score == 5) {
            npc2_X = 0;
        }
    }

    else if(score > 8) {
        
        // if (score == 6) {
        //     n2posY[0] == lastY2;
        //     n2posX[0] == 0;
        // }

        if (count2 == 0 && count != 0) {
            randomDirection2();
            //npc2Direction = npc3Direction;
            count2 = 10;
        }

        else if (count2 == 0) {
            count2 = 1;
        }

        if (n2posX[0] < 16) {
            if (!upDown) {
                if (n2posY[0] < 20) {
                    npc2Direction = 1;
                }
                else {
                    npc2Direction = -1;
                }
                upDown = true;
            }

            else {
                npc2Direction = 2;
                upDown = false;
            }
        }

        else if (n2posX[0] > 36) {
            if (!upDown) {
                if (n2posY[0] < 16) {
                    npc2Direction = 1;
                }
                else {
                    npc2Direction = -1;
                }
                upDown = true;
            }

            else {
                npc2Direction = -2;
                upDown = false;
            }
        }

        
        if (n2posY[0] < 3) {
            if (upDown) {
                if (n2posX[0] > 16 ) {
                npc2Direction = -2;
                }
                else {
                npc2Direction = 2;
                }
                upDown = false;
            }
            else {
                npc2Direction = 1;
                upDown = true;
            }
        }
        
        if (n2posY[0] > 36) {
            if (upDown) {
                if (n2posX[0] > 16 ) {
                npc2Direction = -2;
                }
                else {
                npc2Direction = 2;
                }
                upDown = false;
            }
            else {
                npc2Direction = -1;
                upDown = true;
            }
        }

        for (int n2 = npc2_length - 1; n2 > 0; n2--) { // previous snake block switched; note head a index 0
            n2posX[n2] = n2posX[n2 - 1];
            n2posY[n2] = n2posY[n2 - 1];
        }
        if (npc2Direction == 1) {
            n2posY[0]++;
        }
        else if (npc2Direction == -1) {
            n2posY[0]--;
        }
        else if (npc2Direction == 2) {
            n2posX[0]++;
        }
        else if (npc2Direction == -2) {
            n2posX[0]--;
        }
        for (int n2 = 0; n2 < npc2_length; n2++) {
            glColor3f(1.0, 0.0, 0.0); 
            glRectd(n2posX[n2], n2posY[n2], n2posX[n2] + 1, n2posY[n2] + 1);
        }
        glColor3f(0.0, 1.0, 0.0);

        for(int n2 = 0; n2 < npc2_length; n2++) { // ends game if snake hits npc
            for (int u2 = 0; u2 < 5; u2++) {
                if(n2posX[n2] == posX[u2] && n2posY[n2] == posY[u2] ) {
                    gameOver =true;
                }
            }
        }

        count2 --;
    }
      else {
        lastY2 = npc2_Y;
    }
}

int lastY3;
int n3posX[30] = {4};  
int n3posY[30] = {lastY3};
int npc3_Y = 1; // y start position of npc3

void drawNPC3(int npc3_X) {
    if (score <= 5) {
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

        if (score == 5) {
            npc3_Y = 0;
        }
    }


    else if(score > 5) {
        
        if (score == 6) {
            n3posY[0] == 5;
        }

        if (count == 0) {
            randomDirection();
            count = 12;
        }


        if (n3posX[0] < 3) {
            if (!upDown) {
                if (n3posY[0] < 16) {
                    npc3Direction = 1;
                }
                else {
                    npc3Direction = -1;
                }
                upDown = true;
            }

            else {
                npc3Direction = 2;
                upDown = false;
            }
        }

        else if (n3posX[0] > 36) {
            if (!upDown) {
                if (n3posY[0] < 16) {
                    npc3Direction = 1;
                }
                else {
                    npc3Direction = -1;
                }
                upDown = true;
            }

            else {
                npc3Direction = -2;
                upDown = false;
            }
        }

        
        if (n3posY[0] < 3) {
            if (upDown) {
                if (n3posX[0] > 16 ) {
                npc3Direction = -2;
                }
                else {
                npc3Direction = 2;
                }
                upDown = false;
            }
            else {
                npc3Direction = 1;
                upDown = true;
            }
        }
        
        if (n3posY[0] > 16) {
            if (upDown) {
                if (n3posX[0] > 8 ) {
                npc3Direction = -2;
                }
                else {
                npc3Direction = 2;
                }
                upDown = false;
            }
            else {
                npc3Direction = -1;
                upDown = true;
            }
        }

        for (int n = npc4_length - 1; n > 0; n--) { // previous snake block switched; note head a index 0
            n3posX[n] = n3posX[n - 1];
            n3posY[n] = n3posY[n - 1];
        }
        if (npc3Direction == 1) {
            n3posY[0]++;
        }
        else if (npc3Direction == -1) {
            n3posY[0]--;
        }
        else if (npc3Direction == 2) {
            n3posX[0]++;
        }
        else if (npc3Direction == -2) {
            n3posX[0]--;
        }
        for (int n = 0; n < npc4_length; n++) {
            glColor3f(1.0, 0.0, 0.0); 
            glRectd(n3posX[n], n3posY[n], n3posX[n] + 1, n3posY[n] + 1);
        }
        glColor3f(0.0, 1.0, 0.0);

        for(int n = 0; n < npc4_length; n++) { // ends game if snake hits npc
            for (int u3 = 0; u3 < 5; u3++){
                if(n3posX[n] == posX[u3] && n3posY[n] == posY[u3] ) {
                    gameOver =true;
                }
            }
        }

        count --;
    }
      else {
        lastY3 = npc3_Y;
    }
}





void drawSnake() {
    for (int i = snakeLength - 1; i > 0; i--) { // previous snake block switched; note head a index 0
        posX[i] = posX[i - 1];
        posY[i] = posY[i - 1];
    }
    if (snakeDirection == 1) {
        posY[0]++;
    }
    else if (snakeDirection == -1) {
        posY[0]--;
    }
    else if (snakeDirection == 2) {
        posX[0]++;
    }
    else if (snakeDirection == -2) {
        posX[0]--;
    }
    for (int i = 0; i < snakeLength; i++) {
        if (i == 0 ) { // head will be green
            glColor3f(0.0, 1.0, 0.0); 
        }
        else { // non head will be blue
            glColor3f(0.0, 0.0, 1.0); 
        }
        glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
    }

    for(int i = 1; i < snake_length; i++) { // ends game if snake hits npc
        if(posX[i] == npc1_X && posY[i] == 5 && score < 5) {
            gameOver =true;
        }

        else if(posX[i] == npc2_X && posY[i] == 25 && score < 5 ) {
            gameOver =true;
        } 

        else if(posX[i] == 4 && posY[i] == npc3_Y && score < 5 ) {
            gameOver =true;
        }

        else if(posX[i] == 12 && posY[i] == npc3_Y && score > 10 ) {
            gameOver =true;
        }

    }
    
    if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 2) { // check if snake has been in red area
        gameOver = true;
    }
    if (posX[0] == foodX && posY[0] == foodY) { // if head reaches food
        score++;
        if (npc4_length < 20 && score > 5) {
            npc4_length += 2;
            npc2_length += 2;
        }
        food = true;
    }

    // update score board if gameOver
    if (gameOver == true) {
        scores.push_back(score);

        std::sort(scores.begin(), scores.end(), std::greater<int>());
        highestScores.assign(scores.begin(), scores.begin() + 3);
    }
}

void drawScore() {
    char scoreStr[15]; // max chars is 15
    snprintf(scoreStr, sizeof(scoreStr), "SCORE: %d", score);
    glColor3f(0, 1.0, 0);
    glRasterPos2f(0, 40);
    
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)scoreStr);
}

void drawGameStart() {
    // draw start screen snake
    if (startPosX[0] == 28 && startPosY[0] == 11) {
        startDirection = 1;
    }
    if (startPosX[0] == 28 && startPosY[0] == 29) {
        startDirection = -2;
    }
    if (startPosX[0] == 9 && startPosY[0] == 29) {
        startDirection = -1;
    }
    if (startPosX[0] == 9 && startPosY[0] == 11) {
        startDirection = 2;
    }
    for (int i = startSnakeLength - 1; i > 0; i--) { // previous snake block switched; note head a index 0
        startPosX[i] = startPosX[i - 1];
        startPosY[i] = startPosY[i - 1];
    }
    if (startDirection == 1) {
        startPosY[0]++;
    }
    else if (startDirection == -1) {
        startPosY[0]--;
    }
    else if (startDirection == 2) {
        startPosX[0]++;
    }
    else if (startDirection == -2) {
        startPosX[0]--;
    }
    for (int i = 0; i < snakeLength; i++) {
        if (i == 0 ) { // head will be green
            glColor3f(0.0, 1.0, 0.0); 
        }
        else { // non head will be blue
            glColor3f(0.0, 0.0, 1.0); 
        }
        glRectd(startPosX[i], startPosY[i], startPosX[i] + 1, startPosY[i] + 1);
    }

    // displays "LEGLESS REPTILE"
    glColor3f(0.0, 1.0, 0);
    glRasterPos2f(13, 25);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"LEGLESS REPTILE");

    glColor3f(0.0, 1.0, 0);
    glRasterPos2f(12.5, 16);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"USE ARROW KEYS TO MOVE!");

    // displays "PRESS 'ENTER' TO START"
    glColor3f(0.0, 1.0, 0);
    glRasterPos2f(13.5, 15);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"PRESS 'ENTER' TO START");
    // displays "PRESS 'ESC' TO EXIT"
    glRasterPos2f(14.5, 14);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"PRESS 'ESC' TO EXIT");

    // displays flashing "START"
    startFlash++;
    if (startFlash == 14) {
        startFlash = 0;
    }
    if (startFlash < 7) {
        glColor3f(0.0, 1.0, 0);
        glRasterPos2f(17, 20);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"START");
    }
}

void drawGameOver() {
    // displays "GAME OVER"
    endFlash++;
    if (endFlash == 14) {
        endFlash = 0;
    }
    if (endFlash < 7) {
        glColor3f(1.0, 0, 0);
        glRasterPos2f(14, 29.5);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"GAME OVER");
    }

    // displays your score
    char scoreStr[15]; // max chars is 15
    snprintf(scoreStr, sizeof(scoreStr), "YOUR SCORE: %d", score);
    glColor3f(0, 1.0, 0);
    glRasterPos2f(14.5, 28);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)scoreStr);

    // displays "PRESS 'ENTER' TO PLAY AGAIN"
    glColor3f(0, 0, 1.0);
    glRasterPos2f(11.5, 26.5);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"PRESS 'ENTER' TO PLAY AGAIN");

    // displays "PRESS 'ESC' TO EXIT"
    glRasterPos2f(14, 25.5);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"PRESS 'ESC' TO EXIT");

    // displays leaderboard
    glColor3f(1.0, 1.0, 0);
    glRasterPos2f(13, 20);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"LEADERBOARD: ");
    
    // displays 1st place
    bool youDisplayed = false;
    char firstPlace[15]; // max chars is 15
    if (highestScores.at(0) == score) {
        snprintf(firstPlace, sizeof(firstPlace), "1ST: %d (YOU)", highestScores.at(0));
        youDisplayed = true;
    }
    else {
        snprintf(firstPlace, sizeof(firstPlace), "1ST: %d", highestScores.at(0));
    }
    glColor3f(1, 0.078, 0.576);
    glRasterPos2f(17, 18);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)firstPlace);   

    // displays 2nd place
    char secondPlace[15]; // max chars is 15
    if (highestScores.at(1) == score && !youDisplayed) {
        snprintf(secondPlace, sizeof(secondPlace), "2ND: %d (YOU)", highestScores.at(1));
        youDisplayed = true;
    }
    else {
        snprintf(secondPlace, sizeof(secondPlace), "2ND: %d", highestScores.at(1));
    }
    glColor3f(0, 1.0, 1.0);
    glRasterPos2f(17, 16);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)secondPlace);

    // displays 3rd place
    char thirdPlace[15]; // max chars is 15
    if (highestScores.at(2) == score && !youDisplayed) {
        snprintf(thirdPlace, sizeof(thirdPlace), "3RD: %d (YOU)", highestScores.at(2));
    }
    else {
        snprintf(thirdPlace, sizeof(thirdPlace), "3RD: %d", highestScores.at(2));
    }
    glColor3f(1.0, 0.647, 0);
    glRasterPos2f(17, 14);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)thirdPlace);
}

void reset() {
    snakeDirection = 2; // snake direction: 1 = up, -1 = down, 2 = right, -2 = left
    npc3Direction = -1;
    npc3Direction = 1;
    score = 0;
    gameOver = 0;
    snake_length = 5;
    npc4_length = 0;
    npc2_length = 0;
    posX[0] = 20;
    posX[1] = 20;
    posX[2] = 20;
    posX[3] = 20;
    posX[4] = 20;
    posY[0] = 20;
    posY[1] = 19;
    posY[2] = 18;
    posY[3] = 17;
    posY[4] = 16;

    n3posY[0] = 3;
    n3posX[0] = 3;
    n2posY[0] = 3;
    n2posX[0] = 3;

    for (int j = 1; j < npc2_length; j++) {
        n3posX[j] = 0;
        n3posY[j] = 0;
        n2posX[j] = 0;
        n2posY[j] = 0;
    }
    npc1_Y = 30;
    food = true;
    right1 = true;
    right2 = true;
    up = true;
}