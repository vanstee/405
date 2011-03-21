#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

#define WIDTH       800
#define HEIGHT      600
#define ROTFACTOR   0.2
#define XLATEFACTOR 0.5

#define ABS(x) x < 0 ? -x : x

static double pan      = 0;
static double tilt     = 0;
static double approach = 0;
static double thetax   = 0;
static double thetay   = 0;
static int mousex      = 0;
static int mousey      = 0;
static int button      = -1;


void init() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);      
  
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
  gluPerspective(60, (GLfloat)WIDTH / (GLfloat)HEIGHT, 1, 100);
  glMatrixMode(GL_MODELVIEW);  
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
  // keyboard
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  init();
  glutMainLoop();
}