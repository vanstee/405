#ifndef _H_Light
#define _H_Light

#include "Vector.h"
#include "Color.h"
#include "Sphere.h"
using namespace std;

class Light;

class Light {
	public:
		Vector3d center;
		Color color;
		Light(Vector3d, Color);
	  Color diffuse(Vector3d, Vector3d, Sphere);
	  Color specular(Vector3d, Vector3d, Sphere);
};

#endif
