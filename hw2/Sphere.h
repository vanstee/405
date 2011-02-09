#ifndef _H_Sphere
#define _H_Sphere

#include "Vector.h"
using namespace std;

class Sphere;

class Sphere {
	public:
		double x, y, z, radius;
		string color;
		Sphere(double, double, double, double, string);
		~Sphere();
		double closest_hit(Vector3d, Vector3d);
		double radius_squared();		
};

#endif
