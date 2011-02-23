#ifndef _H_Camera
#define _H_Camera

#include <fstream>
#include "Vector.h"
using namespace std;

class Camera;

class Camera {
	public:
		Vector3d vp, v, vup;
		double focal, width, height, pwidth, pheight, xoffset, yoffset;
		Camera(Vector3d, Vector3d, Vector3d, double, double, double, double);
		Vector3d p(int, int, Vector3d, Vector3d);
};

#endif
