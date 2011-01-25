/*
   Sample OpenGL/GLUT Program to Draw a Square and Save to an Image File
 
   Program opens a window and draws a colored square on a white background

   Colors cycle through R, Y, G, C, B, M with 'c' keypress
   Display window saved to a file with 'w' keypress
   Program quits when either 'q' or ESC are pressed

   CP SC 405/605            Donald H. House         1/20/2011

   usage: glmagick
*/

#include <Magick++.h>
#include <cstdlib>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;
using namespace Magick;

#define WIDTH	     	600	/* window dimensions */
#define HEIGHT		600

static int icolor = 0;

/*
  Routine to write the current framebuffer to an image file
*/
void writeimage(){
  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  unsigned char pixmap[4 * w * h];
  string outfilename;

  glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixmap);
  Image image(w, h, "RGBA", CharPixel, (void *)pixmap);

  cout << "enter output image filename: ";
  cin >> outfilename;

  image.write(outfilename);
}

/*
   Display Callback Routine: clear the screen and draw a square
   This routine is called every time the window on the screen needs
   to be redrawn, like if the window is iconized and then reopened
   by the user, and when the window is first created. It is also
   called whenever the program calls glutPostRedisplay()
*/
void drawSquare(){
  // red, yellow, green, cyan, blue, magenta
  float colors[6][3] = {{1, 0, 0}, {1, 1, 0}, {0, 1, 0},
			{0, 1, 1}, {0, 0, 1}, {1, 0, 1}};
  
  glClear(GL_COLOR_BUFFER_BIT);  // clear window to background color
    
  // set the drawing color
  glColor3f(colors[icolor][0], colors[icolor][1], colors[icolor][2]);
  
  // draw the square
  glBegin(GL_POLYGON);
    glVertex2i(100, 100);
    glVertex2i(100, 500);
    glVertex2i(500, 500);
    glVertex2i(500, 100);
  glEnd();

  // flush the OpenGL pipeline to the viewport
  //glFlush();
  glutSwapBuffers();
}

/*
  Keyboard Callback Routine: 'c' cycle through colors, 'q' or ESC quit
  This routine is called every time a key is pressed on the keyboard
*/
void handleKey(unsigned char key, int x, int y){
  
  switch(key){
    case 'c':		// 'c' - cycle to next color
    case 'C':
      icolor = (icolor + 1) % 6;
      glutPostRedisplay();
      break;
      
    case 'w':
    case 'W':
      writeimage();
      break;
      
    case 'q':		// q - quit
    case 'Q':
    case 27:		// esc - quit
      exit(0);
      
    default:		// not a valid key -- just ignore it
      return;
  }
}

/*
 Reshape Callback Routine: sets up the viewport and drawing coordinates
 This routine is called when the window is created and every time the window 
 is resized, by the program or by the user
*/
void handleReshape(int w, int h){
  // make the viewport the entire window
  glViewport(0, 0, w, h);
  
  // define the drawing coordinate system on the viewport
  // to be measured in pixels
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);
}

/*
   Main program to draw the square, change colors, and wait for quit
*/
int main(int argc, char* argv[]){

  // start up the glut utilities
  glutInit(&argc, argv);

  // create the graphics window, giving width, height, and title text
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("A Simple Square");

  // set up the callback routines to be called when glutMainLoop() detects
  // an event
  glutDisplayFunc(drawSquare);	  // display callback
  glutKeyboardFunc(handleKey);	  // keyboard callback
  glutReshapeFunc(handleReshape); // window resize callback
  
  // specify window clear (background) color to be opaque white
  glClearColor(1, 1, 1, 1);

  // Routine that loops forever looking for events. It calls the registered 
  // callback routine to handle each event that is detected
  glutMainLoop();
  return 0;
}
