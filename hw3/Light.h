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
	  virtual Color diffuse(Vector3d, Vector3d, Sphere) = 0;
		virtual Color specular(Vector3d, Vector3d, Sphere) = 0;
};

#endif
