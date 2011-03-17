// Description:
// This is a solution to homework project 3 with basic requirements implemented.
// Since it's a raycaster vectors are pointed through the pixels that make up the image
// and are colored depending on what they hit (or nothing at all). The color is then
// adjusted depending on the the ambient, diffuse and specular lights. The camera can be 
// specified in camera.txt.
// 
// Name: Patrick Van Stee
// 
// Date: February 23, 2011
// 
// Instructions:
// $ make clean && make
// $ ./shady [l|v] [pixwidth] [filename.ext]
// Press w to write the display to the file specified in as the [filename.ext] option
// Press q or ESC to quit the program
// 
// Example camera.txt:
// 0.0 0.0 0.5     # viewpoint
// 0.0 0.0 -1.0    # view direction
// 1.0 0.0 0.0     # up direction
// 0.5             # focal length
// 1.25            # aspect ratio
// 0.5             # screen width

#include <Magick++.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
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

Camera *camera;

Light *lights[3] = {
	new PointLight(Vector3d( 2, 0.5,  0), Color(1.0, 1.0, 0.9)),
	new PointLight(Vector3d( 1, 0.5, -5), Color(0.9, 0.9, 1.0)),
	new PointLight(Vector3d(-1, 1.0,  5), Color(1.0, 1.0, 0.9))
};
 
Sphere *spheres[5] = {
	new Sphere(Vector3d(-0.30,  0.10, -0.50), 0.050, Material(Color(1.0, 0.0, 0.0), 0.1, 0.2, 100)),
	new Sphere(Vector3d( 0.00, -0.20, -0.80), 0.150, Material(Color(0.0, 1.0, 0.0), 0.1, 0.2, 100)),
	new Sphere(Vector3d( 0.30,  0.30, -1.10), 0.300, Material(Color(0.0, 0.0, 1.0), 0.1, 0.2, 100)),
	new Sphere(Vector3d( 0.10,  0.20, -0.30), 0.075, Material(Color(1.0, 0.5, 0.0), 0.1, 0.2, 100)),			
	new Sphere(Vector3d(-0.20, -0.25, -0.40), 0.225, Material(Color(0.5, 0.0, 1.0), 0.1, 0.2, 100)) 
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

// parse camera.txt for camera
void initCamera(const char* filename, double columns) {
	ifstream file;
	file.open(filename);
	file.is_open();
	if(!file.fail()) {
		int line_number = 0;
		double x, y, z, focal, aspect, width;
		Vector3d vp, v, vup;
		char line[64];

		file.getline(line, 64);
		sscanf(line, "%lf %lf %lf", &x, &y, &z);
		vp = Vector3d(x, y, z);

		file.getline(line, 64);
		sscanf(line, "%lf %lf %lf", &x, &y, &z);
		v = Vector3d(x, y, z);

		file.getline(line, 64);
		sscanf(line, "%lf %lf %lf", &x, &y, &z);
		vup = Vector3d(x, y, z);

		file.getline(line, 64);
		sscanf(line, "%lf", &focal);

		file.getline(line, 64);
		sscanf(line, "%lf", &aspect);

		file.getline(line, 64);
		sscanf(line, "%lf", &width);

		camera = new Camera(vp, v, vup, focal, aspect, width, columns);
	}
	else {
		camera = new Camera(Vector3d(0, 0, 1), Vector3d(0, 0, -1), Vector3d(0, 1, 0), 0.5, 1.25, 0.5, double(width)); 
	}
}

void drawScene() {
	// get the axises
	Vector3d ux = (camera->v % camera->vup).normalize();
	Vector3d uy = camera->vup.normalize();
	Vector3d uz = -camera->v.normalize();
	Vector3d origin = camera->vp - (camera->focal * uz);
	
	// loop over every pixel
	for(int row = 0; row < image.rows(); row++) {
		for(int col = 0; col < image.columns(); col++) {
			Vector3d p = origin + camera->p(row, col, ux, uy);
			Vector3d ur = perspective ? (p - camera->vp).normalize() : -uz;

			double distance, min = -1;
			Sphere* sphere;
			
			
			// loop over the spheres
			for(int i = 0; i < 5; i++) {
				distance = spheres[i]->intersection(p, ur);
				if(distance > 0 && (min < 0 || distance < min)) {
					min = distance;
					sphere = spheres[i];
				}
			}

			Color color(0, 0, 0);
			  
			// if a sphere is hit loop over the lights
			if(min > 0) {
				Color ambient = sphere->material.color * sphere->material.ambient;
				Color diffuse(0, 0, 0);
				Color specular(0, 0, 0);
				Vector3d hit = p + (ur * min);				
				for(int i = 0; i < 3; i++) {
					diffuse = diffuse + lights[i]->diffuse(ur, hit, *sphere);
					specular = specular + lights[i]->specular(ur, hit, *sphere);
				}
				
        Color reflection = Light::reflection(*sphere, ur, hit, spheres, lights, 0);
				
				// total up the color
				color = ambient + diffuse + specular + reflection;
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
	
	// parse command line arguments
	for(int i = 0; i < argc; i++) {
		if(strcmp(argv[i], "v") == 0 || strcmp(argv[i], "l") == 0) {
			perspective = strcmp(argv[i], "v") == 0;
		} else if(atoi(argv[i]) != 0) {
			width = atoi(argv[i]);
		} else {
			filename = string(argv[i]);
		}
	}
	
	// parse camera.txt for camera
	initCamera("camera.txt", width);
	
	stringstream dimensions;
	dimensions << camera->columns << "x" << camera->rows;
	
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
