#ifndef _H_Sphere
#define _H_Sphere

#include "Vector.h"
#include "Color.h"
using namespace std;

class Sphere;

class Sphere {
	public:
		double x, y, z, radius;
		Color color;
		Sphere(double, double, double, double, double, double, double);
		~Sphere();
		double closest_hit(Vector3d, Vector3d);
		double radius_squared();
};

#endif
