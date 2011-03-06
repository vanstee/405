// This is just a class to split up some of the hit logic

#include "Camera.h"

using namespace std;

Camera::Camera(Vector3d vp, Vector3d v, Vector3d vup, double focal, double aspect, double width, double columns) :
							 vp(vp), v(v), vup(vup), focal(focal), width(width), height(width / aspect), columns(columns), rows(columns / aspect) {
								
	vup = vup.normalize();
	
	// check if the image should be in landscape or portrait 
	if(!(vup == Vector3d(0.0, 1.0, 0.0) || vup == Vector3d(0.0, -1.0, 0.0))) {
		this->width = height;
		this->height = width;
		this->columns = rows;
		this->rows = columns;		
	}
	
	pwidth = this->width / this->columns;
	pheight = this->height / this->rows;
	xoffset = (this->width / 2) - (pwidth / 2);
	yoffset = (this->height / 2) - (pheight / 2);
}
	
Vector3d Camera::p(int row, int col, Vector3d ux, Vector3d uy) {
	double px = (col * pwidth) - xoffset;			
	double py = (row * pheight) - yoffset;
	return (px * ux) + (py * uy);
}
