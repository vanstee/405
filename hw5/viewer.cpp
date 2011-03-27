#include <cstdlib>

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
#define ROTFACTOR   0.2
#define XLATEFACTOR 0.5

#define ABS(x) x < 0 ? -x : x

static bool perspective, wireframe, pointlight;
static double pan, tilt, approach, thetax, thetay;
static int button;
static int mousex, mousey;
static int width, height;

const GLfloat LIGHTPOS[] = {-6,  6,  6,  1};
const GLfloat LIGHTDIR[] = { 0,  0, -1,  0};
const GLfloat WHITE[]    = { 1,  1,  1,  1};

void init() {
  perspective = false;
  wireframe   = true;
  pointlight  = false;
  pan         = 0;
  tilt        = 0;
  approach    = 0;
  thetax      = 0;
  thetay      = 0;
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
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);  
  glLightfv(GL_LIGHT0, GL_AMBIENT, WHITE);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);  
}

void wirecube() { 
  glBegin(GL_LINE_LOOP);
    glNormal3f( 0,  0,  1);
    glVertex3f(-1, -1,  1);
    glVertex3f( 1, -1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f(-1,  1,  1);
  glEnd();
  glBegin(GL_LINE_LOOP);
    glNormal3f( 0,  0, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1,  1, -1);
    glVertex3f( 1,  1, -1);
    glVertex3f( 1, -1, -1);
  glEnd();
  glBegin(GL_LINE_LOOP);
    glNormal3f( 1,  0,  0);
    glVertex3f( 1, -1,  1);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1,  1, -1);
    glVertex3f( 1,  1,  1);    
  glEnd();
  glBegin(GL_LINE_LOOP);
    glNormal3f(-1,  0,  0);
    glVertex3f(-1, -1,  1);
    glVertex3f(-1,  1,  1);
    glVertex3f(-1,  1, -1);
    glVertex3f(-1, -1, -1);    
  glEnd();
  glBegin(GL_LINE_LOOP);
    glNormal3f( 0,  1,  0);
    glVertex3f(-1,  1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1,  1, -1);
    glVertex3f(-1,  1, -1);
  glEnd();
  glBegin(GL_LINE_LOOP);
    glNormal3f( 0, -1,  0);
    glVertex3f(-1, -1,  1);
    glVertex3f(-1, -1, -1);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1, -1,  1);
  glEnd();  
}

void solidcube() {
  glBegin(GL_POLYGON);
    glNormal3f( 0,  0,  1);
    glVertex3f(-1, -1,  1);
    glVertex3f( 1, -1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f(-1,  1,  1);
  glEnd();
  glBegin(GL_POLYGON);
    glNormal3f( 0,  0, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1,  1, -1);
    glVertex3f( 1,  1, -1);
    glVertex3f( 1, -1, -1);
  glEnd();
  glBegin(GL_POLYGON);
    glNormal3f( 1,  0,  0);
    glVertex3f( 1, -1,  1);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1,  1, -1);
    glVertex3f( 1,  1,  1);    
  glEnd();
  glBegin(GL_POLYGON);
    glNormal3f(-1,  0,  0);
    glVertex3f(-1, -1,  1);
    glVertex3f(-1,  1,  1);
    glVertex3f(-1,  1, -1);
    glVertex3f(-1, -1, -1);    
  glEnd();
  glBegin(GL_POLYGON);
    glNormal3f( 0,  1,  0);
    glVertex3f(-1,  1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1,  1, -1);
    glVertex3f(-1,  1, -1);
  glEnd();
  glBegin(GL_POLYGON);
    glNormal3f( 0, -1,  0);
    glVertex3f(-1, -1,  1);
    glVertex3f(-1, -1, -1);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1, -1,  1);
  glEnd();
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
  
  if(wireframe)
    wirecube();
  else
    solidcube();
  
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
  
  if(pointlight)
    glLightfv(GL_LIGHT0, GL_POSITION, LIGHTPOS);
  else
    glLightfv(GL_LIGHT0, GL_POSITION, LIGHTDIR);

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
      pan -= ROTFACTOR * dy;
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