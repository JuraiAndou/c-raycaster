#include "GL/freeglut_std.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1024
#define HEIGHT 512

typedef struct {
    float x_position;
    float y_position;
    GLfloat red = 1;
    GLfloat green = 1;
    GLfloat blue = 0;
} Player;

Player player = {0};

void drawPlayer () {
    glColor3f(player.red, player.green, player.blue);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(player.x_position, player.y_position);
    glEnd();
}

void display () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawPlayer();
    glutSwapBuffers();
}

void buttons (unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            player.x_position -= 5;
            break;
        case 'd':
            player.x_position += 5;
            break;
        case 'w':
            player.y_position -= 5;
            break;
        case 's':
            player.y_position += 5;
            break;
    }
    glutPostRedisplay();
}

void init () {
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    player.x_position = 300;
    player.y_position = 300;
}

int main (int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("test");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutMainLoop();
    
    return 0;
}
