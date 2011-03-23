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

static bool perspective = false;
static double pan       = 0;
static double tilt      = 0;
static double approach  = 0;
static double thetax    = 0;
static double thetay    = 0;
static int mousex       = 0;
static int mousey       = 0;
static int button       = -1;
static int width;
static int height;

const GLfloat LIGHTPOS[] = {-6, 6, 6, 1};
const GLfloat WHITE[]    = {1, 1, 1, 1};

void init() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);  
  glLightfv(GL_LIGHT0, GL_AMBIENT, WHITE);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
  glLightfv(GL_LIGHT0, GL_POSITION, LIGHTPOS);  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); 
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
  
  glutSolidCube(2);
  
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

  glMatrixMode(GL_MODELVIEW);  
  
  ::width = width;
  ::height = height;  
}

void keyboard(unsigned char key, int x, int y) {
  switch(key) {
    case 'p':
    case 'P':
      perspective = !perspective;
      reshape(width, height);
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
      // initial state
      break;
    case 'q':
    case 'Q':
    case ESC:
      exit(0);
  }
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
  init();
  glutMainLoop();
  return 0;
}