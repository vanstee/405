// Description:
// This is a solution to homework project 1 with both basic requirements 
// and advanced extension implemented.
//
// Name: Patrick Van Stee
//
// Date: Javuary 25, 2011
//
// Instructions:
// $ make clean && make
// $ ./imgview or ./imgview image.jpg
// Press r to read and display a new image form a file
// Press w to write the currently displayed image to a file
// Press q or ESC to quit the program

#include <Magick++.h>
#include <cstdlib>
#include <iostream>
#include <string>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;
using namespace Magick;

Image image("640x480", "black");
const PixelPacket* pixmap;
const int GL_TYPE = QuantumDepth == 8 ? GL_UNSIGNED_BYTE : GL_UNSIGNED_SHORT;

void imageToPixmap() {
	image.flip();
	pixmap = image.getConstPixels(0, 0, image.columns(), image.rows());
}

void pixmapToImage() {
	PixelPacket* pixels = image.setPixels(0, 0, image.columns(), image.rows());
	*pixels = *pixmap;
	image.syncPixels();
	image.flip();
}

void readImage(string filename) {
	if(filename.empty()) {
		cout << "Enter input image filename: ";
		cin >> filename;		
	}
	image.read(filename);
}

void writeImage() {
	string filename;
	cout << "Enter output image filename: ";
	cin >> filename;
	image.write(filename);
}

void handleDisplay() {
  glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0, 0);
	glDrawPixels(image.columns(), image.rows(), GL_BGRA, GL_TYPE, pixmap);
	glutSwapBuffers();
}

void handleKeyboard(unsigned char key, int x, int y){
  switch(key){
    case 'r':
    case 'R': 
			readImage(""); 
			imageToPixmap();
			glutReshapeWindow(image.columns(), image.rows());			
			handleDisplay();
			break;
			
    case 'w':
    case 'W': 
			pixmapToImage();
			writeImage();
			break;
			
    case 'q':
    case 'Q':
    case 27: 
			exit(0);
			
    default: 
			return;
  }
}

void handleReshape(int w, int h) {
	float ratio = 1.0;
	
	if(w < image.columns() || h < image.rows()) {
		const float xratio = w / (image.columns() * 1.0);
		const float yratio = h / (image.rows() * 1.0);
		ratio = xratio < yratio ? xratio : yratio;
		glPixelZoom(ratio, ratio);
	}
	
	const int x = (int)((w - (image.columns() * ratio)) / 2);
	const int y = (int)((h - (image.rows() * ratio)) / 2);
	glViewport(x, y, w - x, h - y);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]){
	if(argc > 1) {
		image.read(string(argv[1]));
	}
	
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(image.columns(), image.rows());
  glutCreateWindow("Get the Picture!");

	imageToPixmap();

  glutDisplayFunc(handleDisplay);
  glutKeyboardFunc(handleKeyboard);
  glutReshapeFunc(handleReshape);
  
  glClearColor(0, 0, 0, 0);

  glutMainLoop();
  return 0;
}
