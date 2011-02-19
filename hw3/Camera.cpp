// This is just a class to split up some of the hit logic

#include "Camera.h"

using namespace std;

Camera::Camera(Vector3d vp, Vector3d v, Vector3d vup, double focal, double aspect, double width, double columns) :
							 vp(vp), v(v), vup(vup), focal(focal), width(width), height(width * aspect) {
	pwidth = width / columns;
	pheight = height / (columns / aspect);
	xoffset = (width / 2) - (pwidth / 2);
	yoffset = (height / 2) - (pheight / 2);
}
	
Vector3d Camera::p(int row, int col) {
	double px = (col * pwidth) - xoffset;			
	double py = (row * pheight) - yoffset;
	return Vector3d(px, py, 0);
}
