#include "Sphere.h"

using namespace std;

Sphere::Sphere(double x, double y, double z, double radius, string color):
	x(x), y(y), z(z), radius(radius), color(color) {}

Sphere::~Sphere() {}

double Sphere::closest_hit(Vector3d ur, Vector3d p) {
	Vector3d c(this->x, this->y, this->z);
	Vector3d cur = (c - p);
	double t = ur * cur;
	Vector3d x = p + (t * ur);
	Vector3d d = c - x;
	double distance = d.norm();
	
	if(distance <= this->radius) {
		//printf("%f %f\n", this->radius_squared(), (distance * distance));
		double a = sqrt(this->radius_squared() - (distance * distance));
		x = x - (x * a);
		return x.norm();
	}
	else {
		return -1.0;
	}
}

double Sphere::radius_squared() {
	return this->radius * this->radius;
}