// This is just a class to split up some of the hit logic

#include "ParallelLight.h"

using namespace std;
						
ParallelLight::ParallelLight(Vector3d ul, Color color) :
	Light(ul, color) {}

Color ParallelLight::diffuse(Vector3d ur, Vector3d hit, Sphere sphere) {
	return Light::diffuse(ul, ur, hit, sphere);
}

Color ParallelLight::specular(Vector3d ur, Vector3d hit, Sphere sphere) {
	return Light::specular(ul, ur, hit, sphere);
}
