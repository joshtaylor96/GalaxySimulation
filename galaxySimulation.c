////////////////////////////////////////////////////////////////
// School of Computer Science
// The University of Manchester
//
// This code is licensed under the terms of the Creative Commons 
// Attribution 2.0 Generic (CC BY 3.0) License.
//
// Skeleton code for COMP37111 coursework, 2013-14
// (Authors: Arturs Bekasovs and Toby Howard)
// 
// Main Code Author: Joshua Taylor, 2018 
//
//
/////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#ifdef MACOSX
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

GLfloat position = 1.0;
static int i;
static int numStars = 100;

typedef struct {
  GLfloat x;
  GLfloat y;
  GLfloat z;
  GLfloat mass;
  GLfloat xVelocity;
  GLfloat yVelocity;
  GLfloat zVelocity;
} Star;

#define MAX_STARS 1000
Star starArray[MAX_STARS];

// Display list for coordinate axis 
GLuint axisList;

int AXIS_SIZE= 200;
int axisEnabled= 1;

///////////////////////////////////////////////

GLfloat myRandom()
//Return random GLfloat within range [-1,1]
{
  return ((rand()/(GLfloat)RAND_MAX)*2)-1;
}

void updatePosition(void)
{
  for (i=0; i<numStars; i++)
  {
    starArray[i].x += starArray[i].xVelocity;
    starArray[i].y += starArray[i].yVelocity;
    starArray[i].z += starArray[i].zVelocity;
  }
  glutPostRedisplay();
}

void initStarArray(void)
{
  for (i=0; i<numStars; i++)
  {
    starArray[i].x = 0;
    starArray[i].y = 0;
    starArray[i].z = 0;
    starArray[i].xVelocity = 0.1 * myRandom();
    starArray[i].yVelocity = 0.1 * myRandom();
    starArray[i].zVelocity = 0.1 * myRandom();
    starArray[i].mass = 1;
  }
}

///////////////////////////////////////////////

void display()
{
  glLoadIdentity();
  gluLookAt(0.0, 100.0, 1000.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);
  // If enabled, draw coordinate axis
  if(axisEnabled) glCallList(axisList);

  glColor3f(1.0, 0.0, 0.0);
  glPointSize(1.0);

  glBegin(GL_POINTS);
    for (i=0; i<numStars; i++)
    {
      glVertex3f(starArray[i].x, starArray[i].y, starArray[i].z);
    }
  glEnd();

  glutSwapBuffers();
}

///////////////////////////////////////////////

void keyboard(unsigned char key, int x, int y)
{
  if(key == 27) exit(0);
  if (key == 32) initStarArray();
  glutPostRedisplay();
}

///////////////////////////////////////////////

void reshape(int width, int height)
{
  glClearColor(0.9, 0.9, 0.9, 1.0);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
  glMatrixMode(GL_MODELVIEW);
}

///////////////////////////////////////////////

void makeAxes() {
// Create a display list for drawing coord axis
  axisList = glGenLists(1);
  glNewList(axisList, GL_COMPILE);
      glLineWidth(2.0);
      glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);       // X axis - red
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(AXIS_SIZE, 0.0, 0.0);
      glColor3f(0.0, 1.0, 0.0);       // Y axis - green
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, AXIS_SIZE, 0.0);
      glColor3f(0.0, 0.0, 1.0);       // Z axis - blue
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, AXIS_SIZE);
    glEnd();
  glEndList();
}

///////////////////////////////////////////////
void initGraphics(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutCreateWindow("COMP37111 Particles");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  makeAxes();
}

/////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  double f;
  initStarArray();
  srand(time(NULL));
  initGraphics(argc, argv);
  glEnable(GL_POINT_SMOOTH);
  glutIdleFunc(updatePosition);
  glutMainLoop();
}
