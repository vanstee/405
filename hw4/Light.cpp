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

Color Light::reflection(Sphere sphere, Vector3d ur, Vector3d hit, Sphere *spheres[5], Light *lights[3], int level) {
  if(level > REFLECTION_LIMIT) return Color(0.0, 0.0, 0.0);
  
  Vector3d n = (hit - sphere.center).normalize();
  double b = ur * n;
  Vector3d um = ur - (2 * b * n);
  
	double distance, min = -1;  
  
	for(int i = 0; i < 5; i++) {
		distance = spheres[i]->intersection(hit, um);
		if(distance > 0 && (min < 0 || distance < min)) {
			min = distance;
			sphere = *spheres[i];
		}
	}
  
	if(min > 0) {	  
    hit = hit + (um * min);	  
		Color ambient = sphere.material.color * sphere.material.ambient;
		Color diffuse(0, 0, 0);
		Color specular(0, 0, 0);		
		for(int i = 0; i < 3; i++) {
			diffuse = diffuse + lights[i]->diffuse(um, hit, sphere);
			specular = specular + lights[i]->specular(um, hit, sphere);
		}
    level++;
	  return ambient + diffuse + specular + ((1/level) * reflection(sphere, um, hit, spheres, lights, level));
	}
	else {
    return Color(0.0, 0.0, 0.0);
	}
}