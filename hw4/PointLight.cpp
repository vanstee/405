// This is just a class to split up some of the hit logic

#include "PointLight.h"

using namespace std;
						
PointLight::PointLight(Vector3d center, Color color) :
 	Light(center, color) {}

Color PointLight::diffuse(Vector3d ur, Vector3d hit, Sphere sphere) {
	Vector3d ul = (hit - center).normalize();
	return Light::diffuse(ul, ur, hit, sphere);
}

Color PointLight::specular(Vector3d ur, Vector3d hit, Sphere sphere) {
	Vector3d ul = (hit - center).normalize();
	return Light::specular(ul, ur, hit, sphere);
}
