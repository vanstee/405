#ifndef _H_PointLight
#define _H_PointLight

#include "Vector.h"
#include "Color.h"
#include "Sphere.h"
#include "Light.h"
using namespace std;

class PointLight;

class PointLight : public Light {
	public:
		PointLight(Vector3d, Color);
	  Color diffuse(Vector3d, Vector3d, Sphere);
	  Color specular(Vector3d, Vector3d, Sphere);
};

#endif
