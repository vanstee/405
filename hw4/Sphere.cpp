// This is just a class to split up some of the hit logic

#include "Sphere.h"

using namespace std;

Sphere::Sphere(Vector3d center, double radius, Material material) : 
	center(center), radius(radius), material(material) {}

double Sphere::intersection(Vector3d p, Vector3d ur) {
	Vector3d cur = (center - p);
	double t = ur * cur;
	Vector3d x = p + (t * ur);
	Vector3d d = center - x;
	double distance = d.norm();
	
	if(distance <= radius) {
		double a = sqrt(pow(radius, 2) - pow(distance, 2));
		return t - a;
	}
	else {
		return -1.0;
	}
}
