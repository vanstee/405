#ifndef _H_Material
#define _H_Material

#include "Color.h"
using namespace std;

class Material;

class Material {
	public:
		Color color;
		double ambient, diffuse, specular;
		Material(Color, double, double, double);
};

#endif
