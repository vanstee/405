// This is just a class to split up some of the hit logic

#include "PointLight.h"

using namespace std;
						
PointLight::PointLight(Vector3d center, Color color) :
	Light(center, color) {}

Color PointLight::diffuse(Vector3d ur, Vector3d hit, Sphere sphere) {
	Vector3d ul = (hit - center).normalize();
	Vector3d n = (hit - sphere.center).normalize();
	double k = -(ul * n);
	if(k > 0) {
		return k * color * sphere.material.color * sphere.material.diffuse;
	}
	return Color(0.0, 0.0, 0.0);
}

Color PointLight::specular(Vector3d ur, Vector3d hit, Sphere sphere) {
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
