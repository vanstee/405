#include <cstdlib>
#include <cstdio>
#include <cmath>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

#define Abs(x)		(((x) < 0) ? (-(x)) : (x))

#define ESC         27
#define WIDTH       800
#define HEIGHT      600
#define NONE        -1
#define DRAWWIDTH   32
#define DRAWHEIGHT  24
#define NEAR        10
#define FAR         100
#define DEPTH		    -4
#define SOLIDWIDTH  2
#define SOLIDHEIGHT 2
#define SOLIDDEPTH  2
#define ROTFACTOR   0.2
#define XLATEFACTOR 0.5

static bool Perspective;
static int Width;
static int Height;
static double Pan;
static double Tilt;
static double Approach;
static double ThetaX;
static double ThetaY;
static int MouseX;
static int MouseY;
static int Button = NONE;

const float WHITE[] = {1, 1, 1, 1};
const float MEDGREY[] = {0.5, 0.5, 0.5, 1};
const float LightPosition[] = {-6, 6, 6, 1};

void setInitialState() {
  Perspective = false;
  
  //glDisable(GL_LIGHTING);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);  
  glShadeModel(GL_SMOOTH);
  glLightfv(GL_LIGHT0, GL_AMBIENT, MEDGREY);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, MEDGREY);
  glLightfv(GL_LIGHT0, GL_SPECULAR, MEDGREY);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); 
  

  Pan = 0;
  Tilt = 0;
  Approach = DEPTH;

  ThetaX = 0;
  ThetaY = 0;
}

void updateProjection(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  if(!Perspective)
    glOrtho(-DRAWWIDTH/2, DRAWWIDTH/2, -DRAWHEIGHT/2, DRAWHEIGHT/2, NEAR, FAR);
  else
    glFrustum(-DRAWWIDTH/2, DRAWWIDTH/2, -DRAWHEIGHT/2, DRAWHEIGHT/2, NEAR, FAR);

  glMatrixMode(GL_MODELVIEW);
}

void drawCube(float width, int height, int depth) {
  glutSolidCube(2);
  
  /*glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MEDGREY);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDGREY);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MEDGREY);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);  
  glBegin(GL_POLYGON);	// Front Face
    glNormal3f(0, 0, 1);  
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
  glEnd();
  glBegin(GL_POLYGON);	// Back Face
    glNormal3f(0, 0, -1);  
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
  glEnd();
  glBegin(GL_POLYGON);	// Right Face
    glNormal3f(1, 0, 0);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
  glEnd();
  glBegin(GL_POLYGON);	// Left Face
    glNormal3f(-1, 0, 0);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
  glEnd();
  glBegin(GL_POLYGON);	// Top Face
    glNormal3f(0, 1, 0);  
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
  glEnd();
  glBegin(GL_POLYGON);	// Bottom Face
    glNormal3f(0, -1, 0);  
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
  glEnd();*/
}

void drawModel(){
  //glColor3f(0.3, 0.3, 1.0);
  //glLineWidth(2);
  drawCube(SOLIDWIDTH, SOLIDHEIGHT, SOLIDDEPTH);
}

void doDisplay(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glRotatef(Tilt, 1, 0, 0);
  glRotatef(Pan, 0, 1, 0);
  glTranslatef(0, 0, Approach);

  glRotatef(ThetaY, 0, 1, 0);
  glRotatef(ThetaX, 1, 0, 0);

  glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
  glPopMatrix();

  drawModel();
    
  glutSwapBuffers();
}

void handleKey(unsigned char key, int x, int y) {
  switch(key) {
    case 'p':
    case 'P':
      Perspective = !Perspective;
      updateProjection(Width, Height);
      glutPostRedisplay();
      break;
    case 'w':
    case 'W':
      // wireframe or shaded
      break;
    case 'l':
    case 'L':
      // infinite or point light
      break;      
    case 'i':
    case 'I':
      setInitialState();
      updateProjection(Width, Height);
      glutPostRedisplay();
      break;
    case 'q':
    case 'Q':
    case ESC:
      exit(0);
  }
}

void handleButtons(int button, int state, int x, int y) {
  if(state == GLUT_UP)
    Button = NONE;
  else {
    MouseY = -y;
    MouseX = x;
    Button = button;
  }
}

void handleMotion(int x, int y) {
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
      delta = Abs(dx) > Abs(dy) ? dx : dy;
      Approach += XLATEFACTOR * delta;
      glutPostRedisplay();
      break;
  }

  MouseX = x;
  MouseY = y;
}

void doReshape(int width, int height){
  Width = width;
  Height = height;
  updateProjection(Width, Height);
}

void initialize(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0, 0, 0, 0);
  setInitialState();
}

int main(int argc, char* argv[]){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("OpenGL Viewer");
  glutDisplayFunc(doDisplay);
  glutReshapeFunc(doReshape);
  glutKeyboardFunc(handleKey);
  glutMouseFunc(handleButtons);
  glutMotionFunc(handleMotion);
  initialize();
  glutMainLoop();
}
