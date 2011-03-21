/*
  shader.cpp

  CP SC 405/605 Computer Graphics    Donald H. House     9/15/08
  Sample Solution to Quiz 3, question 2.

  Demonstrate how shading is affected by viewer and light position.

  OpenGL/GLUT Program to view 4 surfaces with a single point light
  source, as depicted in midterm exam question 11. Each surface has
  different ambient, diffuse and specular shading parameters. This
  program allows the user to move the camera or the light on a
  circular track and see how this affects the shading of the surfaces.
 
  The program uses color coding to show the various lighting
  effects. Ambient light is colored blue, diffuse light is colored
  yellow and specular light is colored white.

  Keyboard keypresses have the following effects:
    i       	- reinitialize (reset program to initial default state)
    m		- toggle between camera and light movement coupled to mouse
    c		- toggle between materials greyscale or color coded
    q or Esc	- quit

  Camera and light controls following the mouse: draging the mouse
    left or right with the left-button down, causes either the camera
    or the light source to move in the direction indicated by the
    mouse.

  To compile on linux:
    g++ -o shader shader.cpp -lglut -lGL -lm
*/

#include <cstdlib>
#include <cstdio>
#include <cmath>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

//*****************************************************************
//  Demo Code
//*****************************************************************

#define FALSE		0
#define TRUE		1

#define ESC		27	// numeric code for keyboard Esc key

#define WIDTH           800	// initial window dimensions
#define HEIGHT          600

#define NONE		-1	// used to indicate no mouse button pressed

#define NEAR		1	// distance of near clipping plane
#define FAR		500	// distance of far clipping plane

#define VIEWWIDTH	1.155 * NEAR // viewplane width = 2/sqrt(3) NEAR, 60 degree visual angle 

#define DEPTH		250    // z coord. of camera relative to center of world.

#define MAXROTATION     85     // maximum rotation of camera and light in degrees
#define DEFAULTROTATION 60     // default rotation of camera and light in degrees

#define ROTFACTOR	0.2    // degrees rotation/unit mouse movement

// colors for lights and materials
const float LTBLUE[] = {0.2, 0.2, 0.8, 1};
const float DKBLUE[] = {0.05, 0.05, 0.2, 1};
const float DKGREY[] = {0.2, 0.2, 0.2, 1};
const float MEDGREY[] = {0.6, 0.6, 0.6, 1};
const float LTGREY[] = {0.8, 0.8, 0.8, 1};
const float WHITE[] = {1, 1, 1, 1};
const float BLACK[] = {0, 0, 0, 1};
const float LTYELLOW[] = {0.8, 0.8, 0.2, 1};
const float MEDYELLOW[] = {0.6, 0.6, 0.15, 1};
const float DKYELLOW[] = {0.2, 0.2, 0.05, 1};
const float HIGHLIGHT[] = {0.6, 0.6, 0.6, 1};

// position of light before rotation
const float LightPosition[] = {0, 0, DEPTH, 1};

//
// Global variables updated and shared by callback routines
//

// Window dimensions
static double Width = WIDTH;
static double Height = HEIGHT;

// False - camera is being moved, True - light is being moved
static double MoveLight;

// True - materials are color coded, False - materials are white
static int UseColor;

// Camera and light orientation
static double CameraPan;
static double LightPan;

// global variables to track mouse and shift key
static int MouseX;
static int MouseY;
static int Button = NONE;

//
// Routine to initialize the state of the program to start-up defaults
//
void setInitialState(){
  
  // make sure that surface normals are unit direction vectors
  glEnable(GL_NORMALIZE);
  
  // interpolate shading across the surface
  glShadeModel(GL_SMOOTH);

  // local lighting, consider position of light in specular shading
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  
  // make sure light 0 is emitting white light
  glLightfv(GL_LIGHT0, GL_AMBIENT, WHITE);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);

  // initial make sure that lighting and light 0 are turned on
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // initial camera and light orientations
  CameraPan = -DEFAULTROTATION;
  LightPan = DEFAULTROTATION;
}

void updateProjection(){

  // initialize the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // determine the projection system and drawing coordinates
  double xmax = VIEWWIDTH / 2;
  double ymax = (float(Height) / float(Width)) * xmax;
  glFrustum(-xmax, xmax, -ymax, ymax, NEAR, FAR);

  // restore modelview matrix as the one being updated
  glMatrixMode(GL_MODELVIEW);
}

//
// routine to draw a rectangular face centered at the origin
//
void drawFace(float size){
#define N 16
#define NFACETS (N * N)
  int i, j;
  float w = size / N;
  
  glPushMatrix();
  // tile the face with NFACETS squares so good lighting is obtained
  glTranslatef(-size / 2 + w, -size / 2 + w, 0);
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(-w / 2, -w / 2, w / 2);
        glVertex3f(w / 2, -w / 2, w / 2);
		glVertex3f(w / 2, w / 2, w / 2);
		glVertex3f(-w / 2, w / 2, w / 2);
      glEnd();
      glTranslatef(w, 0, 0);
    }
    glTranslatef(-size, w, 0);
  }
  glPopMatrix();
}

//
// Draw the four flat surfaces in front of camera
//
void drawModel(){
  static int SIZE = 45;

  glPushMatrix();    
    glTranslatef(-75, 0, 0);
    if(UseColor){
      glMaterialfv(GL_FRONT, GL_AMBIENT, LTBLUE);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, DKYELLOW);
    }
    else{
      glMaterialfv(GL_FRONT, GL_AMBIENT, LTGREY);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, DKGREY);
    }
    glMaterialfv(GL_FRONT, GL_SPECULAR, BLACK);
    glMaterialf(GL_FRONT, GL_SHININESS, 0);
    drawFace(SIZE);
    
    glTranslatef(50, 0, 0);
    if(UseColor){
      glMaterialfv(GL_FRONT, GL_AMBIENT, DKBLUE);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, LTYELLOW);
    }
    else{
      glMaterialfv(GL_FRONT, GL_AMBIENT, DKGREY);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, LTGREY);
    }
    drawFace(SIZE);
    
    glTranslatef(50, 0, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, BLACK);
    if(UseColor)
      glMaterialfv(GL_FRONT, GL_DIFFUSE, MEDYELLOW);
    else
      glMaterialfv(GL_FRONT, GL_DIFFUSE, MEDGREY);
    glMaterialfv(GL_FRONT, GL_SPECULAR, HIGHLIGHT);
    glMaterialf(GL_FRONT, GL_SHININESS, 2);
    drawFace(SIZE);
    
    glTranslatef(50, 0, 0);
    glMaterialf(GL_FRONT, GL_SHININESS, 90);
    drawFace(SIZE);
  glPopMatrix();
}

//
// Display callback
//
void doDisplay(){
  
  // clear the window to the background color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // establish camera coordinates
  glLoadIdentity();
  
  glTranslatef(0, 0, -DEPTH);
  glRotatef(-CameraPan, 0, 1, 0);    // pan - rotate camera about y, about the center of scene

  // place the light
  glPushMatrix();
    glRotatef(LightPan, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);   // rotate light about y about center of scene 
  glPopMatrix();
  
  // draw the model
  drawModel();
    
  glutSwapBuffers();
}

//
// Keyboard callback routine. 
// Set various modes or take actions based on key presses
//
void handleKey(unsigned char key, int x, int y){

  switch(key){

  case 'i':			// I -- reinitialize 
  case 'I':
    setInitialState();
    glutPostRedisplay();
    break;

  case 'm':			// M -- toggle light or camera movement 
  case 'M':
    MoveLight = !MoveLight;
    setInitialState();
    glutPostRedisplay();
    break;

  case 'c':
  case 'C':
    UseColor = !UseColor;
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
// on button press, record mouse position and which button pressed
//
void handleButtons(int button, int state, int x, int y){

  if(state == GLUT_UP)
    Button = NONE;	// no button pressed
  else{
    MouseY = -y;	// invert y window coord to correspond with OpenGL
    MouseX = x;
    Button = button;	// store which button pressed
  }
}

//
// Mouse Motion Callback
// when mouse moves with left button down, update either camera or light angle
//
void handleMotion(int x, int y){
  int delta;

  y = -y;
  int dy = y - MouseY;
  int dx = x - MouseX;

  switch(Button){
  case GLUT_LEFT_BUTTON:
    if(MoveLight){
      LightPan += ROTFACTOR * dx;
      LightPan = (LightPan > MAXROTATION? MAXROTATION: LightPan < -MAXROTATION? -MAXROTATION: LightPan);      
    }
    else{
      CameraPan += ROTFACTOR * dx;
      CameraPan = (CameraPan > MAXROTATION? MAXROTATION: CameraPan < -MAXROTATION? -MAXROTATION: CameraPan);
    }
    glutPostRedisplay();
    break;
  }

  MouseX = x;
  MouseY = y;
}

//
// Reshape Callback
// Keep viewport the entire screen
//
void doReshape(int width, int height){

  glViewport(0, 0, width, height);
  Width = width;
  Height = height;

  updateProjection();
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
  
  MoveLight = FALSE;
  UseColor = FALSE;
}

//
// Main program to create window, setup callbacks, and initiate GLUT
//
int main(int argc, char* argv[]){

  // start up the glut utilities
  glutInit(&argc, argv);

  // create the graphics window, giving width, height, and title text
  // and establish double buffering, RGBA color, and a depth buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Surface Shade Viewer");

  // register callback to draw graphics when window needs updating
  glutDisplayFunc(doDisplay);
  glutReshapeFunc(doReshape);
  glutKeyboardFunc(handleKey);
  glutMouseFunc(handleButtons);
  glutMotionFunc(handleMotion);

  initialize();

  glutMainLoop();
  return 0;
}
