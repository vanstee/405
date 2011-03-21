/*
  Interactive OpenGL "hello world" program

  hello.cpp

  Clemson University Computer Graphics    Donald H. House     3/8/11

  OpenGL/GLUT Program to View a 3D rectangular solid in wireframe

  The rectangular solid is positioned with its center at (0, 0, -50). Its
  width is 20, its height is 16, and its depth is 10.

  The window is initially set to 800 x 600 pixels.
  The camera viewscreen width is 32 and height is 24

  Keyboard keypresses have the following effects:
    i       	- reinitialize (reset program to initial default state)
    p		- toggle between orthographic and perspective view
    q or Esc	- quit

  Camera and model controls following the mouse:
    model yaw   - left-button, horizontal motion, rotation of the model around the y axis
    model tilt  - left-button, vertical motion, rotation of the model about the x axis
    camera yaw  - middle-button, horizontal motion, rotation of the camera about the y axis
    camera tilt	- middle-button, vertical motion, rotation of the camera about the x axis
    approach    - right-button, vertical or horizontal motion, translation of camera along z axis

  usage: hello
*/

#include <cstdlib>
#include <cstdio>
#include <cmath>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include "Matrix.h"

using namespace std;

//*****************************************************************
//  Demo Code
//*****************************************************************

#define ESC		27	// numeric code for keyboard Esc key

#define WIDTH           800	// initial window dimensions
#define HEIGHT          600

#define NONE		-1	// used to indicate no mouse button pressed

// view volume dimensions
#define DRAWWIDTH	32	// width and
#define DRAWHEIGHT	24	// height should be in same ratio as window
#define NEAR		10	// distance of near clipping plane
#define FAR		100	// distance of far clipping plane

// object size and position
#define DEPTH		-50	// initial z coord. of center of solid (center x = y = 0)
#define SOLIDWIDTH	20	// width dimension of the solid
#define SOLIDHEIGHT	16	// height dimension of the solid
#define SOLIDDEPTH	10	// depth dimension of the solid

#define ROTFACTOR	0.2     // degrees rotation per pixel of mouse movement
#define XLATEFACTOR	0.5     // units of translation per pixel of mouse movement

//
// Global variables updated and shared by callback routines
//

// Viewing parameters
static bool Perspective;  // false = orthographic, true = perspective
static int Width;	  // current window width
static int Height;	  // current window height

// Camera position and orientation
static double Pan;
static double Tilt;
static double Approach;

// model orientation
static double ThetaX;
static double ThetaY;

// global variables to track mouse and shift key
static int MouseX;
static int MouseY;
static int Button = NONE;

//
// Routine to initialize the state of the program to start-up defaults
//
void setInitialState(){

  // initial camera viewing controls
  Perspective = false;
  glDisable(GL_LIGHTING);

  // initial camera orientation and position
  Pan = 0;
  Tilt = 0;
  Approach = DEPTH;

  // initial model orientation
  ThetaX = 0;
  ThetaY = 0;
}

//
// Routine to build the viewport and projection matrices and to
// save the projection matrix
//
void updateProjection(int width, int height){
  // set the viewport to be the entire window
  glViewport(0, 0, width, height);
  
  // initialize the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  // determine the projection system and drawing coordinates
  if(!Perspective)
    glOrtho(-DRAWWIDTH/2, DRAWWIDTH/2, -DRAWHEIGHT/2, DRAWHEIGHT/2, NEAR, FAR);
  else
    glFrustum(-DRAWWIDTH/2, DRAWWIDTH/2, -DRAWHEIGHT/2, DRAWHEIGHT/2, NEAR, FAR);
  
  // restore modelview matrix as the one being updated
  glMatrixMode(GL_MODELVIEW);
}

//
// routine to draw a cube centered at the origin
//
void drawCube(float width, int height, int depth){

  glBegin(GL_LINE_LOOP);	// Front Face
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
  glEnd();
  glBegin(GL_LINE_LOOP);	// Back Face
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
  glEnd();
  glBegin(GL_LINE_LOOP);	// Right Face
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
  glEnd();
  glBegin(GL_LINE_LOOP);	// Left Face
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
  glEnd();
  glBegin(GL_LINE_LOOP);	// Top Face
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
  glEnd();
  glBegin(GL_LINE_LOOP);	// Bottom Face
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
  glEnd();
}

//
// routine to draw the current model
//
void drawModel(){

  // set drawing color to pale blue, and draw with thicker wireframe lines
  glColor3f(0.3, 0.3, 1.0);
  glLineWidth(2);
  drawCube(SOLIDWIDTH, SOLIDHEIGHT, SOLIDDEPTH);
}

//
// Display callback
//
void doDisplay(){
  
  // clear the window to the background color
  glClear(GL_COLOR_BUFFER_BIT);
  
  // initialize the modelview matrix
  glLoadIdentity();

  // establish camera coordinates
  glRotatef(Tilt, 1, 0, 0);	    // tilt - rotate camera about x axis
  glRotatef(Pan, 0, 1, 0);	    // pan - rotate camera about y axis
  glTranslatef(0, 0, Approach);     // approach - translate camera along z axis

  // rotate the model
  glRotatef(ThetaY, 0, 1, 0);       // rotate model about x axis
  glRotatef(ThetaX, 1, 0, 0);       // rotate model about y axis

  // draw the model in wireframe
  drawModel();
    
  glutSwapBuffers();
}

//
// Keyboard callback routine. 
// Set various modes or take actions based on key presses
//
void handleKey(unsigned char key, int x, int y){

  switch(key){

  case 'p':			// P -- toggle between ortho and perspective
  case 'P':
    Perspective = !Perspective;
    updateProjection(Width, Height);
    glutPostRedisplay();
    break;

  case 'i':			// I -- reinitialize 
  case 'I':
    setInitialState();
    updateProjection(Width, Height);
    glutPostRedisplay();
    break;
    
  case 'q':			// Q or Esc -- exit program
  case 'Q':
  case ESC:
    exit(0);
  }
}

//
// Mouse Button Callback
// on button press, record mouse position and which button is pressed
//
void handleButtons(int button, int state, int x, int y){

  if(state == GLUT_UP)
    Button = NONE;		// no button pressed
  else{
    MouseY = -y;		// invert y coordinate to correspond with OpenGL
    MouseX = x;

    Button = button;		// store which button pressed
  }
}

//
// Mouse Motion Callback
// when mouse moves with a button down, update appropriate camera parameter
//
void handleMotion(int x, int y){
  int delta;
  
  y = -y;
  int dy = y - MouseY;
  int dx = x - MouseX;

  switch(Button){
  case GLUT_LEFT_BUTTON:
    ThetaX -= ROTFACTOR * dy;
    ThetaY += ROTFACTOR * dx;
    glutPostRedisplay();
    break;
  case GLUT_MIDDLE_BUTTON:
    Pan -= ROTFACTOR * dx;
    Tilt += ROTFACTOR * dy;
    glutPostRedisplay();
    break;
  case GLUT_RIGHT_BUTTON:
    delta = (Abs(dx) > Abs(dy)? dx: dy);
    Approach += XLATEFACTOR * delta;
    glutPostRedisplay();
    break;
  }

  MouseX = x;
  MouseY = y;
}

//
// Reshape Callback
// Keep viewport, modelview and projection matrices the same as they were,
// even though window resizes
//
void doReshape(int width, int height){
  Width = width;
  Height = height;

  updateProjection(Width, Height);
}

//
// Initialize OpenGL to establish lighting and colors
// and initialize viewing and model parameters
//
void initialize(){
  
  // initialize modelview matrix to identity
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // specify window clear (background) color to be black
  glClearColor(0, 0, 0, 0);

  // initialize viewing and model parameters
  setInitialState();
}

//
// Main program to create window, setup callbacks, and initiate GLUT
//
int main(int argc, char* argv[]){

  // start up the glut utilities
  glutInit(&argc, argv);

  // create the graphics window, giving width, height, and title text
  // and establish double buffering, RGBA color
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("OpenGL Interactive Hello World");

  // register callback to draw graphics when window needs updating
  glutDisplayFunc(doDisplay);
  glutReshapeFunc(doReshape);
  glutKeyboardFunc(handleKey);
  glutMouseFunc(handleButtons);
  glutMotionFunc(handleMotion);

  initialize();

  glutMainLoop();
}
