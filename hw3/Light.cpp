// This is just a class to split up some of the hit logic

#include "Light.h"

using namespace std;

Light::Light(Vector3d vector, Color color) : center(vector), ul(vector.normalize()), color(color) {}

Color Light::diffuse(Vector3d ul, Vector3d ur, Vector3d hit, Sphere sphere) {
	Vector3d n = (hit - sphere.center).normalize();
	double k = -(ul * n);
	if(k > 0) {
		return k * color * sphere.material.color * sphere.material.diffuse;
	}
	return Color(0.0, 0.0, 0.0);
}

Color Light::specular(Vector3d ul, Vector3d ur, Vector3d hit, Sphere sphere) {
	Vector3d n = (hit - sphere.center).normalize();
	double b = ul * n;
	Vector3d ulprime = ul - (2 * b * n);
	double k = ulprime * -ur;
	if(k > 0 && sphere.material.specular > 0) {
		return pow(k, sphere.material.specular) * color * sphere.material.color;
	}
	return Color(0.0, 0.0, 0.0);
}