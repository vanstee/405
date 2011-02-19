// This is just a class to split up some of the hit logic

#include "Light.h"

using namespace std;
						
Light::Light(Vector3d center, Color color) :
	center(center), color(color) {}

Color Light::diffuse(Vector3d ur, Vector3d hit, Sphere sphere) {
	Vector3d ul = (hit - center).normalize();
	Vector3d n = (hit - sphere.center).normalize();
	double k = -(ul * n);
	if(k > 0) {
		return k * color * sphere.material.color * sphere.material.diffuse;
	}
	return Color(0.0, 0.0, 0.0);
}

Color Light::specular(Vector3d ur, Vector3d hit, Sphere sphere) {
	Vector3d ul = (hit - center).normalize();
	Vector3d n = (hit - sphere.center).normalize();
	double b = ul * n;
	Vector3d ulprime = ul - (2 * b * n);
	double k = ulprime * -ur;
	if(k > 0) {
		return pow(k, sphere.material.specular) * color * sphere.material.color;
	}
	return Color(0.0, 0.0, 0.0);
}
