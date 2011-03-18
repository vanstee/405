#ifndef _H_Light
#define _H_Light

#include "Vector.h"
#include "Color.h"
#include "Sphere.h"
using namespace std;

class Light;

class Light {
  static const int REFLECTION_LIMIT = 8;
  
	public:
		Vector3d center, ul;
		Color color;
		Light(Vector3d vector, Color color);
    static Color reflection(Sphere, Vector3d, Vector3d, Sphere**, int, Light**, int, int);
		virtual Color diffuse(Vector3d, Vector3d, Sphere) = 0;
		virtual Color specular(Vector3d, Vector3d, Sphere) = 0;
	protected:
		Color diffuse(Vector3d, Vector3d, Vector3d, Sphere);
		Color specular(Vector3d, Vector3d, Vector3d, Sphere);
};

#endif
