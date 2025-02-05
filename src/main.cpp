#include "includes.h"

#define WIDTH 1024
#define HEIGHT 512
#define P2 M_PI / 2
#define P3 3 * M_PI / 2

typedef struct Player
{
  float x_position;
  float y_position;
  float delta_x;
  float delta_y;
  float angle;
  GLfloat red = 1;
  GLfloat green = 1;
  GLfloat blue = 0;
} Player;

typedef struct Ray
{
  int index;
  int mapHitX;
  int mapHitY;
  int mapPosition;
  int depth_of_field;
  float x;
  float y;
  float angle;
  float x_offset;
  float y_offset;
} Ray;

Player player;

void drawPlayer()
{
  // Draw player cube
  glColor3f(player.red, player.green, player.blue);
  glPointSize(8);
  glBegin(GL_POINTS);
  glVertex2i(player.x_position, player.y_position);
  glEnd();

  // Draw player direction
  glBegin(GL_LINES);
  glVertex2i(player.x_position, player.y_position);
  glVertex2i(player.x_position + player.delta_x * 5,
             player.y_position + player.delta_y * 5);
  glEnd();
}

typedef struct Map
{
  int x = 8;
  int y = 8;
  int size = 64;
} Map;

Map myMap;

int mapArray[] =
    {1, 1, 1, 1, 1, 1, 1, 1,
     1, 0, 1, 0, 0, 0, 0, 1,
     1, 0, 1, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 1,
     1, 0, 0, 0, 0, 1, 0, 1,
     1, 0, 0, 0, 0, 0, 0, 1,
     1, 1, 1, 1, 1, 1, 1, 1};

void drawMap2D()
{
  int x, y, xo, yo;
  for (y = 0; y < myMap.x; y++)
  {
    for (x = 0; x < myMap.y; x++)
    {
      if (mapArray[y * myMap.x + x] == 1)
      {
        glColor3f(1, 1, 1);
      }
      else
      {
        glColor3f(0, 0, 0);
      }

      xo = x * myMap.size;
      yo = y * myMap.size;

      glBegin(GL_QUADS);
      glVertex2i(xo + 1, yo + 1);
      glVertex2i(xo + 1, yo + myMap.size - 1);
      glVertex2i(xo + myMap.size - 1, yo + myMap.size - 1);
      glVertex2i(xo + myMap.size - 1, yo + 1);
      glEnd();
    }
  }
}

void drawRays2D()
{
  Ray ray;
  ray.angle = player.angle;

  for (ray.index = 0; ray.index < 1; ray.index++)
  {
    /**
     * Check horizontal lines
     */
    // ray.depth_of_field = 0;
    // float aTan = -1 / tan(ray.angle); // negative inverse of tangent

    // // Looking up
    // if (ray.angle > M_PI)
    // {
    //   ray.y = (((int)player.y_position >> 6) << 6) - 0.0001; // floor value
    //   ray.x = (player.y_position - ray.y) * aTan + player.x_position;
    //   ray.y_offset = -64;
    //   ray.x_offset = -ray.y_offset * aTan;
    // }

    // // Looking down
    // else if (ray.angle < M_PI)
    // {
    //   ray.y = (((int)player.y_position >> 6) << 6) + 64; // ceiling value
    //   ray.x = (player.y_position - ray.y) * aTan + player.x_position;
    //   ray.y_offset = 64;
    //   ray.x_offset = -ray.y_offset * aTan;
    // }

    // // Looking straight left or right
    // if (ray.angle == 0 || ray.angle == M_PI)
    // {
    //   ray.x = player.x_position;
    //   ray.y = player.y_position;
    //   ray.depth_of_field = 8;
    // }

    // while (ray.depth_of_field < 8)
    // {
    //   ray.mapHitX = (int)(ray.x) >> 6;                       // >> 6 is the same as / 64
    //   ray.mapHitY = (int)(ray.y) >> 6;                       // >> 6 is the same as / 64
    //   ray.mapPosition = ray.mapHitY * myMap.x + ray.mapHitX; // 1D array position

    //   if (ray.mapPosition < myMap.x * myMap.y && mapArray[ray.mapPosition] == 1) // Hit a wall
    //   {
    //     ray.depth_of_field = 8;
    //   }
    //   else
    //   {
    //     ray.x += ray.x_offset;
    //     ray.y += ray.y_offset;
    //     ray.depth_of_field += 1;
    //   }
    //   glColor3f(0, 1, 0);
    //   glLineWidth(1);
    //   glBegin(GL_LINES);
    //   glVertex2i(player.x_position, player.y_position);
    //   glVertex2i(ray.x, ray.y);
    //   glEnd();
    // }

    /**
     * Check vertical lines
     */
    ray.depth_of_field = 0;
    float nTan = -tan(ray.angle); // negative inverse of tangent

    // Looking left
    if (ray.angle > P2 && ray.angle < P3)
    {
      ray.x = (((int)player.x_position >> 6) << 6) - 0.0001; // floor value
      ray.y = (player.x_position - ray.x) * nTan + player.y_position;
      ray.x_offset = -64;
      ray.y_offset = -ray.x_offset * nTan;
    }

    // Looking right
    else if (ray.angle < P2 || ray.angle > P3)
    {
      ray.x = (((int)player.x_position >> 6) << 6) + 64; // ceiling value
      ray.y = (player.x_position - ray.x) * nTan + player.y_position;
      ray.x_offset = 64;
      ray.y_offset = -ray.x_offset * nTan;
    }

    // Looking straight left or right
    if (ray.angle == 0 || ray.angle == M_PI)
    {
      ray.x = player.x_position;
      ray.y = player.y_position;
      ray.depth_of_field = 8;
    }

    while (ray.depth_of_field < 8)
    {
      ray.mapHitX = (int)(ray.x) >> 6;                       // >> 6 is the same as / 64
      ray.mapHitY = (int)(ray.y) >> 6;                       // >> 6 is the same as / 64
      ray.mapPosition = ray.mapHitY * myMap.x + ray.mapHitX; // 1D array position

      if (ray.mapPosition < myMap.x * myMap.y && mapArray[ray.mapPosition] == 1) // Hit a wall
      {
        ray.depth_of_field = 8;
      }
      else
      {
        ray.x += ray.x_offset;
        ray.y += ray.y_offset;
        ray.depth_of_field += 1;
      }
      glColor3f(1, 0, 0);
      glLineWidth(1);
      glBegin(GL_LINES);
      glVertex2i(player.x_position, player.y_position);
      glVertex2i(ray.x, ray.y);
      glEnd();
    }
  }
}
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawMap2D();
  drawRays2D();
  drawPlayer();
  glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y)
{
  if (key == 'a')
  {
    player.angle -= 0.1;
    if (player.angle < 0)
      player.angle += 2 * M_PI;

    player.delta_x = cos(player.angle) * 5;
    player.delta_y = sin(player.angle) * 5;
  }
  if (key == 'd')
  {
    player.angle += 0.1;
    if (player.angle > 2 * M_PI)
      player.angle -= 2 * M_PI;

    player.delta_x = cos(player.angle) * 5;
    player.delta_y = sin(player.angle) * 5;
  }
  if (key == 'w')
  {
    player.x_position += player.delta_x;
    player.y_position += player.delta_y;
  }
  if (key == 's')
  {
    player.x_position -= player.delta_x;
    player.y_position -= player.delta_y;
  }
  glutPostRedisplay();
}

void init()
{
  glClearColor(0.3, 0.3, 0.3, 0);
  gluOrtho2D(0, WIDTH, HEIGHT, 0);
  player.x_position = 300;
  player.y_position = 300;
  player.delta_x = cos(player.angle) * 5;
  player.delta_y = sin(player.angle) * 5;
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
