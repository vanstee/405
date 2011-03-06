#ifndef _H_ParallelLight
#define _H_ParallelLight

#include "Vector.h"
#include "Color.h"
#include "Sphere.h"
#include "Light.h"
using namespace std;

class ParallelLight;

class ParallelLight: public Light {
	public:
		ParallelLight(Vector3d, Color);
	  Color diffuse(Vector3d, Vector3d, Sphere);
	  Color specular(Vector3d, Vector3d, Sphere);
};

#endif
