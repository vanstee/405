#ifndef _H_Sphere
#define _H_Sphere

#include "Vector.h"
#include "Material.h"
using namespace std;

class Sphere;

class Sphere {
	public:
		Vector3d center;
		double radius;
		Material material;
		Sphere(Vector3d, double, Material);
		double intersection(Vector3d, Vector3d);
};

#endif
