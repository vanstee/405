#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define WIDTH  800
#define HEIGHT 600

using namespace std;

void init() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0, 0, 0, 1);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  
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

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("OpenGL Viewer");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  // keyboard
  // mouse
  // motion
  init();
  glutMainLoop();
}