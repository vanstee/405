#ifndef _H_Sphere
#define _H_Sphere

#include "Vector.h"
#include "Color.h"
using namespace std;

class Sphere;

class Sphere {
	public:
		Vector3d center;
		double radius;
		Color color;
		Sphere(Vector3d, double, Color);
		double closest_hit(Vector3d, Vector3d);
		double radius_squared();
};

#endif
