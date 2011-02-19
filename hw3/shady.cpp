// Description:
// This is a solution to homework project 2 with basic requirements implemented.
// Since it's a raycaster vectors are pointed through the pixels that make up the image
// and are colored depending on what they hit (or nothing at all).
//
// Name: Patrick Van Stee
//
// Date: February 9, 2011
//
// Instructions:
// $ make clean && make
// $ ./raycast [l|v] [pixwidth] [filename.ext]
// Press w to write the display to the file specified in as the [filename.ext] option
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
#include "Color.h"
#include "Sphere.h"
#include "Light.h"
#include "PointLight.h"
#include "ParallelLight.h"

using namespace std;

Light *lights[2] = {
	new PointLight(Vector3d(-1.00, 1.00, 0.25), Color(0.4, 0.4, 0.8)),
	new ParallelLight(Vector3d(-sqrt(2.0), -sqrt(2.0), 0.25), Color(0.8, 0.8, 0.2))
};

Sphere *spheres[] = {
	new Sphere(Vector3d(-0.30,  0.10, -0.50), 0.050, Material(Color(1.0, 0.0, 0.0), 0.2, 1.0, 1.0)),
	new Sphere(Vector3d( 0.00, -0.20, -0.80), 0.150, Material(Color(0.0, 1.0, 0.0), 0.2, 0.0, 30.0)),
	new Sphere(Vector3d( 0.30,  0.30, -1.10), 0.300, Material(Color(0.0, 0.0, 1.0), 0.2, 1.0, 30.0)),
	new Sphere(Vector3d( 0.10,  0.20, -0.30), 0.075, Material(Color(1.0, 0.5, 0.0), 0.2, 1.0, 30.0)),			
	new Sphere(Vector3d(-0.20, -0.25, -0.40), 0.225, Material(Color(0.5, 0.0, 1.0), 0.2, 0.5, 0.5))
};

short perspective = true;
string filename = "";
int width = 250;
Magick::Image image;
Magick::PixelPacket* pixmap;
const int GL_TYPE = QuantumDepth == 8 ? GL_UNSIGNED_BYTE : GL_UNSIGNED_SHORT;

void imageToPixmap() {
	image.flip();
	pixmap = image.getPixels(0, 0, image.columns(), image.rows());
}

void pixmapToImage() {
	Magick::PixelPacket* pixels = image.setPixels(0, 0, image.columns(), image.rows());
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
	double pwidth = width / image.columns();
	double pheight = height / image.rows();
	double xoffset = (width / 2) - (pwidth / 2);
	double yoffset = (height / 2) - (pheight / 2);
	
	for(int row = 0; row < image.rows(); row++) {
		for(int col = 0; col < image.columns(); col++) {
			double px = (col * pwidth) - xoffset;			
			double py = (row * pheight) - yoffset;

			Vector3d p(px, py, 0);
			Vector3d ur = perspective ? Vector3d(px, py, -0.5).normalize() : Vector3d(0, 0, -1);
			
			double distance, min = -1;
			Sphere* sphere;
			
			for(int i = 0; i < 5; i++) {
				distance = spheres[i]->intersection(p, ur);
				if(distance > 0 && (min < 0 || distance < min)) {
					min = distance;
					sphere = spheres[i];
				}
			}

			Color color(0, 0, 0);			
			
			if(min > 0) {
				for(int i = 0; i < 2; i++) {
					Vector3d hit = p + (ur * min);
					Color ambient = sphere->material.color * 0.2;
					Color diffuse = lights[i]->diffuse(ur, hit, *sphere);
					Color specular = lights[i]->specular(ur, hit, *sphere);
					color = color + ambient + diffuse + specular;
				}
			}
			
			image.pixelColor(col, row, color.ColorRGB());
		}
	}
	
	image.flip();
	imageToPixmap();
}

int main(int argc, char* argv[]){
	if(argc > 4) {
		cout << "USAGE: raycast [l|v] [pixwidth] [filename.ext]\n";
		exit(1);		
	}
	
	for(int i = 0; i < argc; i++) {
		if(strcmp(argv[i], "v") == 0 || strcmp(argv[i], "l") == 0) {
			perspective = strcmp(argv[i], "v") == 0;
		} else if(atoi(argv[i]) != 0) {
			width = atoi(argv[i]);
		} else {
			filename = string(argv[i]);
		}
	}
	
	int height = int((width / 5.0) * 4);
	
	stringstream dimensions;
	dimensions << width << "x" << height;
	
	image = Magick::Image(dimensions.str(), "black");
	
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
