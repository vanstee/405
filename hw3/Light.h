#ifndef _H_Light
#define _H_Light

#include "Vector.h"
#include "Color.h"
#include "Sphere.h"
using namespace std;

class Light;

class Light {
	public:
		double x, y, z;
		Color color;
		Light(double, double, double, double, double, double);
		~Light();
	  Color diffuse(Vector3d, Vector3d, Sphere);
	  Color specular(Vector3d, Vector3d, Sphere);
};

#endif
