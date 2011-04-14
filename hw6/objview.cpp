// Description:
// This is a solution to homework 6 with the basic fuctionality implemented. 
// The project has a structure similar to my hw5 solution and uses example 
// code from the shader, hello, objload and mipmaps projects, with opengl
// call backs and global variables that contain state information.
// 
// Name: Patrick Van Stee
// 
// Date: April 13, 2011
// 
// Instructions:
// $ make clean && make
// $ ./objview [tetrahedron.obj, cube.obj, Skeleton.obj or Mug.obj]
// Press p to toggle between orthographic and perspective modes
// Press w to toggle between wireframe and shaded viewing modes
// Press l to toggle between a white infinite light and a point light
// Press i to reinitialize the program
// Press s to cycle through ambient only, ambient + diffuse only, and ambient + diffuse + specular shading (advanced)
// Press q or ESC to quit the program

#include <cstdlib>
#include <cstdio>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include "OBJFile.h"
#include "PolySurf.h"

using namespace std;

#define ESC         27
#define WIDTH       800
#define HEIGHT      600
#define NONE        -1
#define DRAWWIDTH   4
#define DRAWHEIGHT  3
#define ROTFACTOR   0.5
#define XLATEFACTOR 0.5

#define ABS(x) (x < 0 ? -x : x)

static bool perspective, wireframe, pointlight;
static int shading;
static double pan, tilt, approach, thetax, thetay;
static int button;
static int mousex, mousey;
static int width, height;

const GLfloat LIGHTPOS[] = {-6,  3,  9,  1};
const GLfloat LIGHTDIR[] = { 0,  0,  1,  0};
const GLfloat WHITE[]    = { 1,  1,  1,  1};
const GLfloat BLACK[]    = { 0,  0,  0,  0};

OBJFile objfile;
PolySurf *polysurf;
Vector3d center;
Vector3d minbox;
Vector3d maxbox;

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
  glShadeModel(GL_SMOOTH);  
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);  
  glEnable(GL_LIGHTING);  
  glLightfv(GL_LIGHT0, GL_POSITION, LIGHTPOS); 
  glLightfv(GL_LIGHT1, GL_POSITION, LIGHTDIR);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1); 
  glEnable(GL_TEXTURE_2D);   
}

void scene(char *argv[]) {
  objfile.setfilename(argv[1]);
  int err = objfile.read();
  polysurf = objfile.getscene();
  center = polysurf->Centroid();
  minbox = polysurf->MinBBox();
  maxbox = polysurf->MaxBBox();  
  
  if(err || polysurf == NULL){
    cerr << "OBJ file " << objfile.getfilename() << " has errors" << endl;
    exit(2);
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(center.x, center.y, center.z + (2 *(maxbox.z - minbox.z)), center.x, center.y, center.z, 0, 1, 0);      
  
  glTranslatef(center.x, center.y, center.z);
  
  glRotatef(tilt, 1, 0, 0);
  glRotatef(pan, 0, 1, 0);
  glTranslatef(0, 0, approach);
  glRotatef(thetay, 0, 1, 0);
  glRotatef(thetax, 1, 0, 0);

  glTranslatef(-center.x, -center.y, -center.z);  
  
  polysurf->Draw(wireframe);
    
  if(pointlight)
    glLightfv(GL_LIGHT0, GL_POSITION, LIGHTPOS);
  
  glutSwapBuffers();
}

void reshape(int width, int height) {  
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  GLfloat objwidth = maxbox.x - minbox.x;
  GLfloat objheight = maxbox.y - minbox.y;
  GLfloat objdepth = maxbox.z - minbox.z;  
  GLfloat drawwidth, drawheight;
  
  GLfloat max = objwidth > objheight ? 
               (objwidth > objdepth ? objwidth : objdepth) : 
               (objheight > objdepth ? objheight * (4.0 / 3.0) : objdepth);
  drawwidth = max;
  drawheight = max * (3.0 / 4.0);
  
  if(perspective)
    glFrustum(-drawwidth, drawwidth, -drawheight, drawheight, 1, 100);
  else
    glOrtho(-drawwidth, drawwidth, -drawheight, drawheight, 1, 100);
  
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
  if(argc != 2) {
    cerr << "usage: objview filename.obj" << endl;
    exit(1);
  }
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("OpenGL Viewer");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  scene(argv);
  setup();
  glutMainLoop();
  return 0;
}
