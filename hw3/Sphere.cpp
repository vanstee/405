// This is just a class to split up some of the hit logic

#include "Sphere.h"

using namespace std;
						
Sphere::Sphere(Vector3d center, double radius, Color color) : 
	center(center), radius(radius), color(color) {}

double Sphere::closest_hit(Vector3d ur, Vector3d p) {
	Vector3d cur = (center - p);
	double t = ur * cur;
	Vector3d x = p + (t * ur);
	Vector3d d = center - x;
	double distance = d.norm();
	
	if(distance <= this->radius) {
		double a = sqrt(this->radius_squared() - (distance * distance));
		return t - a;
	}
	else {
		return -1.0;
	}
}

double Sphere::radius_squared() {
	return this->radius * this->radius;
}
