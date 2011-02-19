// This is just a class to split up some of the hit logic

#include "Light.h"

using namespace std;
						
Light::Light(Vector3d center, Color color) :
	center(center), color(color) {}

Color Light::diffuse(Vector3d ur, Vector3d hit, Sphere sphere) {
	Vector3d ul = (hit - this->center).normalize();
	Vector3d n = (hit - sphere.center).normalize();
	double d = (ul * n) * -1;
	if (d < 0) d = 0;
	return this->color.scale(d).multiply(sphere.color);
}

Color Light::specular(Vector3d ur, Vector3d hit, Sphere sphere) {
	Vector3d ul = (hit - this->center).normalize();
	Vector3d n = (hit - sphere.center).normalize();
	Vector3d ulprime = ul - (2 * (ul * n) * n);
	double d = ulprime * (ur * -1);
	d = d < 0 ? d = 0 : d = pow(d, 10);
	return this->color.scale(d).multiply(sphere.color);
}