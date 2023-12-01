# Arcade
This project is an arcade game similar to "snake". It uses C++ and openGL to take in user input for controlling a playable character, as well as animating things like NPCs and objectives on screen.

This project is split into 3 files:
1. main.cpp - This is where glut and window is initialized and main loop takes place. All the callback functions are defined here and are responsible for keeping the game running.
2. draw.cpp - This is where all the draw functions are defined. Everything here should be called everytime a new frame displays. It updates the position/displays everything on screen. Responsible for drawing game boundaries, playable character, npcs, and objectives.
3. draw.h - This is a header file for draw.cpp that decalres all functions. Necessary in order to use draw functions in main.cpp.

# How to compile, run, & play
To compile/build the program on a linux machine (CSIL), run the following command:
```
make linux
```
Run using:
```
./arcade
```

For mac: 
```
make mac
```
Run using:
```
./arcade
```

Once running, use the arrow keys on the keyboard to control the snake character. Collect as many coins as possible, and don't hit the NPCs or boundaries or else the game will end!