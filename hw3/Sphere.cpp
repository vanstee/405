// This is just a class to split up some of the hit logic

#include "Sphere.h"

using namespace std;

Sphere::Sphere(double x, double y, double z, double radius,
							 double r, double g, double b):
							x(x), y(y), z(z), radius(radius), color(Color(r, g, b)) {}

Sphere::~Sphere() {}

// returns the distance from the sphere to the perspective pixel if there is an intersection
// otherwise it returns -1.0
double Sphere::closest_hit(Vector3d ur, Vector3d p) {
	Vector3d c(this->x, this->y, this->z);
	Vector3d cur = (c - p);
	double t = ur * cur;
	Vector3d x = p + (t * ur);
	Vector3d d = c - x;
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
