// This is just a class to split up some of the hit logic

#include "Light.h"

using namespace std;

Light::Light(double x, double y, double z,
						 double r, double g, double b):
						x(x), y(y), z(z), color(Color(r, g, b)) {}				

Light::~Light() {}

Color Light::diffuse(Vector3d ur, Vector3d hit, Sphere sphere) {
	// -(ul.dot(n)) * cl * cm
	Vector3d l(this->x, this->y, this->z);
	Vector3d s(sphere.x, sphere.y, sphere.z);
	Vector3d ul = (hit - l).normalize();
	Vector3d n = (hit - s).normalize();
	double d = (ul * n) * -1;
	if (d < 0) d = 0;
	return this->color.scale(d).multiply(sphere.color);
}

Color Light::specular(Vector3d ur, Vector3d hit, Sphere sphere) {
	// pow(ulprime.dot(v), sc) * cl * cs
	Vector3d l(this->x, this->y, this->z);
	Vector3d s(sphere.x, sphere.y, sphere.z);	
	Vector3d ul = (hit - l).normalize();
	Vector3d n = (hit - s).normalize();
	Vector3d ulprime = ul - (2 * (ul * n) * n);
	double d = ulprime * (ur * -1);
	d = d < 0 ? d = 0 : d = pow(d, 10);
	return this->color.scale(d).multiply(sphere.color);
}