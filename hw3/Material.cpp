#include "Material.h"

using namespace std;

Material::Material(Color color, double ambient, double diffuse, double specular) :
	color(color), ambient(ambient), diffuse(diffuse), specular(specular) {}
	