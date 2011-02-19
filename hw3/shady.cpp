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

using namespace std;

Light light[1] = {
	Light(-1, 1, 0.25, 0.4, 0.4, 0.8)
};

Sphere sphere[5] = {
	Sphere(-0.30,  0.10, -0.50, 0.050, 1, 0, 0),
	Sphere( 0.00, -0.20, -0.80, 0.150, 0, 1, 0),
	Sphere( 0.30,  0.30, -1.10, 0.300, 0, 0, 1),
	Sphere( 0.10,  0.20, -0.30, 0.075, 1, 0.5, 0),			
	Sphere(-0.20, -0.25, -0.40, 0.225, 0.5, 0, 1)
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
	double pixwidth = width / image.columns();
	double pixheight = height / image.rows();
	double hit, min = -1;
	int hit_index = -1;
	
	for(int row = 0; row < image.rows(); row++) {
		for(int col = 0; col < image.columns(); col++) {
			double px = (col * pixwidth) - (width / 2) - (pixwidth / 2);
			double py = (row * pixheight) - (height / 2) - (pixheight / 2);
			
			Vector3d v = perspective ? Vector3d(0, 0, 0.5) : Vector3d(px, py, 0.5);
			Vector3d p(px, py, 0);
			Vector3d ur = (p - v).normalize();
			Color color(0, 0, 0);
			
			for(int i = 0; i < 5; i++) {
				hit = sphere[i].closest_hit(ur, p);
				if(hit > 0 && (min < 0 || hit < min)) {
					min = hit;
					hit_index = i;
				}
			}
			
			if(min > 0) {
				for(int i = 0; i < 1; i++) {
					Vector3d hit_point = p + (ur * min);
					Color ambient = sphere[hit_index].color.scale(.2);
					Color diffuse = light[i].diffuse(ur, hit_point, sphere[hit_index]);
					Color specular = light[i].specular(ur, hit_point, sphere[hit_index]);
					color = diffuse.add(specular).add(ambient);
				}
			}
			
			Magick::ColorRGB mcolor(
				color.r > 1 ? 1 : color.r, 
				color.g > 1 ? 1 : color.g, 
				color.b > 1 ? 1 : color.b
			);
			image.pixelColor(col, row, mcolor);
			
			min = hit_index = -1;
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
