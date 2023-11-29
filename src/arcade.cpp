#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <GL/freeglut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Your OpenGL rendering code here
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("OpenGL 4.3 with Mesa and FreeGLUT");
    glutDisplayFunc(display);

    // Additional initialization code

    glutMainLoop();
    return 0;
}
