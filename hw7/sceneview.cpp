// Description:
// This is a solution to homework 7 with the basic requirements implemented. 
// The project has a structure similar to the hello and shader example programs, with opengl
// call backs and global variables that contain state information. The model displayed is of
// a simple desk fan. The fan's blades rotate (keys f and v) as well as the base
// (keys g and b), within a defined threshold.
// 
// Name: Patrick Van Stee
// 
// Date: April 27, 2011
// 
// Instructions:
// $ make clean && make
// $ ./viewer
// Press p to toggle between orthographic and perspective modes
// Press w to toggle between wireframe and shaded viewing modes
// Press l to toggle between a white infinite light and a point light
// Press i to reinitialize the program
// Press s to cycle through ambient only, ambient + diffuse only, and ambient + diffuse + specular shading (advanced)
// Press f to rotate the blades counter-clockwise
// Press v to rotate the blades clockwise
// Press g to rotate the base starting to the right
// Press b to rotate the base starting to the left
// Press q or ESC to quit the program

#include <cstdlib>
#include <cstdio>
#include <cmath>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

#define ESC         27
#define WIDTH       800
#define HEIGHT      600
#define NONE        -1
#define DRAWWIDTH   4
#define DRAWHEIGHT  3
#define ROTFACTOR   0.5
#define XLATEFACTOR 0.5
#define PI          3.141592653589793

#define ABS(x) (x < 0 ? -x : x)

static bool perspective, wireframe, pointlight;
static int shading;
static double pan, tilt, approach, thetax, thetay;
static double fantheta, headtheta; 
static bool positivedir;
static int button;
static int mousex, mousey;
static int width, height;

const GLfloat LIGHTPOS[] = {-6,  3,  9,  1};
const GLfloat LIGHTDIR[] = { 0,  0,  1,  0};
const GLfloat WHITE[]    = { 1,  1,  1,  1};
const GLfloat BLACK[]    = { 0,  0,  0,  0};

void init() {
  perspective = false;
  wireframe   = true;
  pointlight  = false;
  pan         = 0;
  tilt        = 0;
  approach    = 0;
  thetax      = 0;
  thetay      = 0;
  fantheta    = 0;
  headtheta   = 0;
  positivedir = true;
  mousex      = 0;
  mousey      = 0;
  button      = -1;
  width       = 800;
  height      = 600;
}

void setup() {
  init();  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);  
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);  
  glEnable(GL_LIGHTING);  
  glLightfv(GL_LIGHT0, GL_POSITION, LIGHTPOS); 
  glLightfv(GL_LIGHT1, GL_POSITION, LIGHTDIR);
  glEnable(GL_LIGHT0);  
  glEnable(GL_LIGHT1);  
}

void base() {
  GLdouble sq2 = sqrt(2) / 2.0;
    
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(   0,  0.2,    0);
    glVertex3f(   0,    0,    1);
    glVertex3f(-sq2,    0,  sq2);
    glVertex3f(  -1,    0,    0);
    glVertex3f(-sq2,    0, -sq2);
    glVertex3f(   0,    0,   -1);
    glVertex3f( sq2,    0, -sq2);
    glVertex3f(   1,    0,    0);
    glVertex3f( sq2,    0,  sq2);  
    glVertex3f(   0,    0,    1);                  
  glEnd();
  
  glBegin(GL_QUAD_STRIP);
    glVertex3f(   0, -0.1,    1);
    glVertex3f(   0,    0,    1);
    glVertex3f( sq2, -0.1,  sq2);
    glVertex3f( sq2,    0,  sq2);
    glVertex3f(   1, -0.1,    0);
    glVertex3f(   1,    0,    0);
    glVertex3f( sq2, -0.1, -sq2);
    glVertex3f( sq2,    0, -sq2);
    glVertex3f(   0, -0.1,   -1);
    glVertex3f(   0,    0,   -1);
    glVertex3f(-sq2, -0.1, -sq2);
    glVertex3f(-sq2,    0, -sq2);
    glVertex3f(  -1, -0.1,    0);
    glVertex3f(  -1,    0,    0);
    glVertex3f(-sq2, -0.1,  sq2);
    glVertex3f(-sq2,    0,  sq2);
    glVertex3f(   0, -0.1,    1);
    glVertex3f(   0,    0,    1);        
  glEnd();
  
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(   0, -0.1,    0);
    glVertex3f(   0, -0.1,    1);
    glVertex3f(-sq2, -0.1,  sq2);
    glVertex3f(  -1, -0.1,    0);
    glVertex3f(-sq2, -0.1, -sq2);
    glVertex3f(   0, -0.1,   -1);
    glVertex3f( sq2, -0.1, -sq2);
    glVertex3f(   1, -0.1,    0);
    glVertex3f( sq2, -0.1,  sq2);
    glVertex3f(   0, -0.1,    1);    
  glEnd();
}

void arm() {
  GLdouble sq2 = sqrt(2) / 2.0;
  
  GLUquadricObj *quad;
  quad = gluNewQuadric();
  
  glPushMatrix(); 
    glRotatef(-90, 1, 0, 0);  
    gluCylinder(quad, 0.25, 0.25, 2, 8, 8);
  glPopMatrix();
    
  glPushMatrix();
    glTranslatef(0, 2, -0.5);
    gluCylinder(quad, 0.25, 0.5, 1, 8, 8);
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(0, 2, -0.5);  
    glRotatef(90, 1, 0, 0);   
    glScalef(0.25, 0.25, 0.25);
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(   0,    0,    0);
      glVertex3f(   0,    0,    1);
      glVertex3f(-sq2,    0,  sq2);
      glVertex3f(  -1,    0,    0);
      glVertex3f(-sq2,    0, -sq2);
      glVertex3f(   0,    0,   -1);
      glVertex3f( sq2,    0, -sq2);
      glVertex3f(   1,    0,    0);
      glVertex3f( sq2,    0,  sq2);
      glVertex3f(   0,    0,    1);    
    glEnd();  
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(0, 2, 0.5);  
    glRotatef(90, 1, 0, 0);   
    glScalef(0.5, 0.5, 0.5);
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(   0,    0,    0);
      glVertex3f(   0,    0,    1);
      glVertex3f(-sq2,    0,  sq2);
      glVertex3f(  -1,    0,    0);
      glVertex3f(-sq2,    0, -sq2);
      glVertex3f(   0,    0,   -1);
      glVertex3f( sq2,    0, -sq2);
      glVertex3f(   1,    0,    0);
      glVertex3f( sq2,    0,  sq2);
      glVertex3f(   0,    0,    1);
    glEnd();  
  glPopMatrix(); 
  
  gluDeleteQuadric(quad);   
}

void blades() { 
  GLdouble sq3 = sqrt(3) / 2.0;
  
  GLUquadricObj *quad;
  quad = gluNewQuadric();  
  
  glPushMatrix();
    glTranslatef(0, 2, 0.5);  
    glRotatef(90, 0, 0, 1);

    glRotatef(20 * fantheta, 0, 0, 1);
    
    glPushMatrix();
      glScalef(1, 1, 0.25);
      gluSphere(quad, 0.5, 8, 8);
    glPopMatrix();
  
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 1, 0);
      glVertex3f(0.5, sq3, 0);
      glVertex3f(sq3, 0.5, 0);
    glEnd();
    
    glRotatef(120, 0, 0, 1);
      
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 1, 0);
      glVertex3f(0.5, sq3, 0);      
      glVertex3f(sq3, 0.5, 0);
    glEnd();
    
    glRotatef(120, 0, 0, 1);
    
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 1, 0);
      glVertex3f(0.5, sq3, 0);      
      glVertex3f(sq3, 0.5, 0);
    glEnd();          
  glPopMatrix();  
  
  gluDeleteQuadric(quad);  
}

void ring(GLdouble radius, GLint slices, GLint stacks) {  
  GLUquadricObj *quad;
  quad = gluNewQuadric();
  
  GLdouble degrees = 360.0 / slices;
  GLdouble length = sin((degrees / 2.0) * (PI / 180)) * 2.0;
  
  glPushMatrix();
    glTranslatef(0, radius, 0);
    for(int i = 1; i <= slices; i++) {
      glPushMatrix();
        glRotatef(90, 0, radius, 0);
        glRotatef((degrees * i) + (degrees / 2.0), 1, 0, 0);  
        glTranslatef(0, 1, -(length / 2.0));  
        gluCylinder(quad, 0.01, 0.01, length, stacks, stacks);
      glPopMatrix();    
    }
  glPopMatrix();
  
  gluDeleteQuadric(quad);
}

void wheel(GLdouble radius, GLint spokes, GLint stacks) {
  GLUquadricObj *quad;
  quad = gluNewQuadric();
  
  GLdouble degrees = 360.0 / spokes;
  
  glPushMatrix();
    glRotatef(90, -1, 0, 0);
    for(double i = 1; i <= spokes; i++) {
      glPushMatrix();
        glRotatef(degrees * i, 0, 1, 0);
        gluCylinder(quad, 0.01, 0.01, radius, stacks, stacks);
      glPopMatrix();        
    }
  glPopMatrix();
  
  gluDeleteQuadric(quad);   
}

void gaurd() {
  GLUquadricObj *quad;
  quad = gluNewQuadric();
  
  glPushMatrix();
    glTranslatef(0, 1, 0.25);
    ring(1, 12, 8);    
    glTranslatef(0, 0, 0.25);
    ring(1, 12, 8);
    glTranslatef(0, 0, 0.25);
    ring(1, 12, 8);        
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(0, 2, 0.25);
    wheel(1, 12, 8);
    glTranslatef(0, 0, 0.5);
    wheel(1, 12, 8);    
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(0, 2, 0.25);
    for(double i = 1; i <= 12; i++) {
      glPushMatrix();
        glRotatef(30 * i, 0, 0, 1);
        glTranslatef(0, 1, 0);
        gluCylinder(quad, 0.01, 0.01, 0.5, 8, 8);
      glPopMatrix();        
    }    
  glPopMatrix();
      
  gluDeleteQuadric(quad);  
} 

void fan() {
  glTranslatef(0, -1, 0);  
  
  base();

  glPushMatrix();
    glRotatef(5 * headtheta, 0, 1, 0);
    arm();    
    blades();
    gaurd();
  glPopMatrix();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0, 0, -4, 0, 0, 0, 0, 1, 0);      
  
  glRotatef(tilt, 1, 0, 0);
  glRotatef(pan, 0, 1, 0);
  glTranslatef(0, 0, approach);
  glRotatef(thetay, 0, 1, 0);
  glRotatef(thetax, 1, 0, 0);
  
  fan();
    
  if(pointlight)
    glLightfv(GL_LIGHT0, GL_POSITION, LIGHTPOS);
  
  glutSwapBuffers();
}

void reshape(int width, int height) {  
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  if(perspective)
    glFrustum(-DRAWWIDTH, DRAWWIDTH, -DRAWHEIGHT, DRAWHEIGHT, 1, 100);
  else
    glOrtho(-DRAWWIDTH, DRAWWIDTH, -DRAWHEIGHT, DRAWHEIGHT, 1, 100);
  
  if(wireframe)
    glDisable(GL_LIGHTING);
  else
    glEnable(GL_LIGHTING);
  
  if(pointlight) {
    glDisable(GL_LIGHT1);
    glEnable(GL_LIGHT0);    
  }
  else {
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);    
  }

  glLightfv(GL_LIGHT0, GL_AMBIENT, WHITE);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);  
  
  glLightfv(GL_LIGHT1, GL_AMBIENT, WHITE);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT1, GL_SPECULAR, WHITE);
  
  switch(shading) {
    case 2:
      glLightfv(GL_LIGHT0, GL_DIFFUSE, BLACK);
      glLightfv(GL_LIGHT1, GL_DIFFUSE, BLACK);
    case 1:
      glLightfv(GL_LIGHT0, GL_SPECULAR, BLACK);
      glLightfv(GL_LIGHT1, GL_SPECULAR, BLACK);
  }
  
  glMatrixMode(GL_MODELVIEW);  
  
  ::width = width;
  ::height = height;  
}

void keyboard(unsigned char key, int x, int y) {
  switch(key) {
    case 'p':
    case 'P':
      perspective = !perspective;
      break;
    case 'w':
    case 'W':
      wireframe = !wireframe;
      break;
    case 'l':
    case 'L':
      pointlight = !pointlight;
      break;      
    case 'i':
    case 'I':
      init();
      break;
    case 's':
    case 'S':
      shading = (shading + 1) % 3;
      break;
    case 'f':
      fantheta++;
      break;
    case 'v':
      fantheta--;    
      break;
    case 'g':
      positivedir = ABS(headtheta) > 9 ? !positivedir : positivedir;
      headtheta = positivedir ? headtheta + 1 : headtheta - 1;
      break;
    case 'b':
      positivedir = ABS(headtheta) > 9 ? !positivedir : positivedir;
      headtheta = positivedir ? headtheta - 1 : headtheta + 1;
      break;
    case 'q':
    case 'Q':
    case ESC:
      exit(0);
  }
  
  reshape(width, height);
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
  if(state == GLUT_UP)
    ::button = -1;
  else {
    mousey = -y;
    mousex = x;
    ::button = button;
  }
}

void motion(int x, int y) {
  y = -y;
  int dy = y - mousey;
  int dx = x - mousex;
  
  switch(button) {
    case GLUT_LEFT_BUTTON:
      thetax -= ROTFACTOR * dy;
      thetay += ROTFACTOR * dx;
      break;      
    case GLUT_MIDDLE_BUTTON:
      pan -= ROTFACTOR * dx;
      tilt += ROTFACTOR * dy;
      break;      
    case GLUT_RIGHT_BUTTON:
      int delta = ABS(dx) > ABS(dy) ? dx : dy;
      approach += XLATEFACTOR * delta;
      break;
  }
  
  glutPostRedisplay();
  
  mousex = x;
  mousey = y;
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("OpenGL Viewer");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  setup();
  glutMainLoop();
  return 0;
}
