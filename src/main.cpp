#include "includes.h"
#include <stdlib.h>

#define WIDTH 1024
#define HEIGHT 512

typedef struct Player
{
  float x_position;
  float y_position;
  GLfloat red = 1;
  GLfloat green = 1;
  GLfloat blue = 0;
} Player;

Player player;

void drawPlayer()
{
  glColor3f(player.red, player.green, player.blue);
  glPointSize(8);
  glBegin(GL_POINTS);
  glVertex2i(player.x_position, player.y_position);
  glEnd();
}

int mapX = 8, mapY = 8, mapS = 64;
int map[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0,
             0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
             0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void drawMap2D()
{
  int x, y, xo, yo;
  for (y = 0; y < mapY; y++)
  {
    for (x = 0; x < mapX; x++)
    {
      if (map[y * mapX + x] == 1)
      {
        glColor3f(1, 1, 1);
      }
      else
      {
        glColor3f(0, 0, 0);
      }

      xo = x * mapS;
      yo = y * mapS;

      glBegin(GL_QUADS);
      glVertex2i(xo + 1, yo + 1);
      glVertex2i(xo + 1, yo + mapS - 1);
      glVertex2i(xo + mapS - 1, yo + mapS - 1);
      glVertex2i(xo + mapS - 1, yo + 1);
      glEnd();
    }
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawMap2D();
  drawPlayer();
  glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y)
{
  /*switch (key) {*/
  /*    case 'a':*/
  /*        player.x_position -= 5;*/
  /*        break;*/
  /*    case 'd':*/
  /*        player.x_position += 5;*/
  /*        break;*/
  /*    case 'w':*/
  /*        player.y_position -= 5;*/
  /*        break;*/
  /*    case 's':*/
  /*        player.y_position += 5;*/
  /*        break;*/
  /*}*/

  if (key == 'a')
  {
    player.x_position -= 5;
  }
  if (key == 'd')
  {
    player.x_position += 5;
  }
  if (key == 'w')
  {
    player.y_position -= 5;
  }
  if (key == 's')
  {
    player.y_position += 5;
  }
  glutPostRedisplay();
}

void init()
{
  glClearColor(0.3, 0.3, 0.3, 0);
  gluOrtho2D(0, WIDTH, HEIGHT, 0);
  player.x_position = 300;
  player.y_position = 300;
}

int main(int argc, char *argv[])
{
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
