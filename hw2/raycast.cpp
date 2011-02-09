// Description:
// This is a solution to homework project 2 with both basic requirements 
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
#include <sstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include "Vector.h"
#include "Sphere.h"

using namespace std;
using namespace Magick;

Sphere sphere[5] = {
	Sphere(-0.30,  0.10, -0.50, 0.050, "red"),
	Sphere( 0.00, -0.20, -0.80, 0.150, "green"),
	Sphere( 0.30,  0.30, -1.10, 0.300, "blue"),
	Sphere( 0.10,  0.20, -0.30, 0.075, "orange"),			
	Sphere(-0.20, -0.25, -0.40, 0.225, "purple")
};

short perspective = true;
string filename = "";
int width = 250;
Image image;
PixelPacket* pixmap;
const int GL_TYPE = QuantumDepth == 8 ? GL_UNSIGNED_BYTE : GL_UNSIGNED_SHORT;

void imageToPixmap() {
	image.flip();
	pixmap = image.getPixels(0, 0, image.columns(), image.rows());
}

void pixmapToImage() {
	PixelPacket* pixels = image.setPixels(0, 0, image.columns(), image.rows());
	*pixels = *pixmap;
	image.syncPixels();
	image.flip();
}

void writeImage() {
	if(filename != "") {
		image.flip();
		image.write(filename);
	}
}

void handleDisplay() {
  glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0, 0);
	glDrawPixels(image.columns(), image.rows(), GL_BGRA, GL_TYPE, pixmap);
	glutSwapBuffers();
}

void handleKeyboard(unsigned char key, int x, int y){
  switch(key){
    case 'w':
    case 'W': 
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

void drawScene() {
	double width = 0.5;
	double height = 0.4;
	double pixwidth = width / image.columns();
	double pixheight = height / image.rows();
	double hit, min;
	
	for(int row = 0; row < image.rows(); row++) {
		for(int col = 0; col < image.columns(); col++) {
			double px = (col * pixwidth) - (width / 2) - (pixwidth / 2);
			double py = (row * pixheight) - (height / 2) - (pixheight / 2);
			
			Vector3d v = perspective ? Vector3d(0, 0, 0.5) : Vector3d(px, py, 0.5);
			Vector3d p(px, py, 0);			
			Vector3d ur = (p - v).normalize();
			
			for(int i = 0; i < 5; i++) {
				hit = sphere[i].closest_hit(ur, p);
				if(hit > 0 && (min < 0 || hit < min)) {
					min = hit;
					image.pixelColor(col, row, sphere[i].color);
				}
			}
			min = -1;
		}
	}
	
	image.flip();
	imageToPixmap();
}

int main(int argc, char* argv[]){
	switch(argc) {
		case 1: break;
		case 2:
			perspective = string(argv[1]).compare("v") == 0;
			break;		
		case 3:
			perspective = string(argv[1]).compare("v") == 0;
			width = atoi(argv[2]);
			break;		
		case 4:
			perspective = string(argv[1]).compare("v") == 0;
			width = atoi(argv[2]);
			filename = string(argv[3]);			
			break;
		default:
			cout << "USAGE: raycast [l|v] [pixwidth] [filename.ext]\n";
			exit(1);
	}
	
	int height = (width / 5.0) * 4;
	
	stringstream dimensions;
	dimensions << width << "x" << height;
	
	image = Image(dimensions.str(), "black");
	
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(image.columns(), image.rows());
  glutCreateWindow("Oh Shoot!");

	drawScene();
  
  glutDisplayFunc(handleDisplay);
  glutKeyboardFunc(handleKeyboard);
  glutReshapeFunc(handleReshape);
  
  glClearColor(0, 0, 0, 0);
  
  glutMainLoop();
  return 0;
}
