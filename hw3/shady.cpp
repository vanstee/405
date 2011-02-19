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
#include "Camera.h"

using namespace std;

Camera *camera = new Camera(Vector3d(0, 0, 0.5), Vector3d(0, 0, -1), Vector3d(0, 1, 0), 0.5, 1.25, 0.5, 600);

Light *lights[2] = {
	new PointLight(Vector3d(-1.00, 1.00, 0.25), Color(0.4, 0.4, 0.8)),
	new ParallelLight(Vector3d(-1.00, -sqrt(6) , -1.00), Color(0.8, 0.8, 0.2))	
};

Sphere *spheres[] = {
	new Sphere(Vector3d(-0.30,  0.10, -0.50), 0.050, Material(Color(1.0, 0.0, 0.0), 0.2, 1.0, 0.0)),
	new Sphere(Vector3d( 0.00, -0.20, -0.80), 0.150, Material(Color(0.0, 1.0, 0.0), 0.2, 0.3, 100.0)),
	new Sphere(Vector3d( 0.30,  0.30, -1.10), 0.300, Material(Color(0.0, 0.0, 1.0), 0.2, 0.5, 20.0)),
	new Sphere(Vector3d( 0.10,  0.20, -0.30), 0.075, Material(Color(1.0, 0.5, 0.0), 0.2, 0.5, 20.0)),			
	new Sphere(Vector3d(-0.20, -0.25, -0.40), 0.225, Material(Color(0.5, 0.0, 1.0), 0.2, 1.0, 0.0))
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
	Vector3d ux = (camera->v % camera->vup).normalize();
	Vector3d uy = camera->vup.normalize();
	Vector3d uz = -camera->v.normalize();
	Vector3d origin = camera->vp - (camera->focal * uz);
	
	for(int row = 0; row < image.rows(); row++) {
		for(int col = 0; col < image.columns(); col++) {
			Vector3d p = origin + camera->p(row, col, ux, uy);
			Vector3d ur = perspective ? (p - camera->vp).normalize() : -uz;

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
				Color ambient = sphere->material.color * sphere->material.ambient;
				Color diffuse(0, 0, 0);
				Color specular(0, 0, 0);
				Vector3d hit = p + (ur * min);				
				for(int i = 0; i < 2; i++) {
					diffuse = diffuse + lights[i]->diffuse(ur, hit, *sphere);
					specular = specular + lights[i]->specular(ur, hit, *sphere);
				}
				color = ambient + diffuse + specular;
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
