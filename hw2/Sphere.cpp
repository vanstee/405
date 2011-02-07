#include "Sphere.h"

using namespace std;

Sphere::Sphere(double a, double b, double c, double d, string e) {
	x = new int;
	y = new int;
	z = new int;
	r = new int;
	color = new string;
	x = a;
	y = b;
	z = c;
	r = d;
	color = e;
}

Sphere::~Sphere(){
  delete x;
  delete y;
  delete z;
  delete r;
  delete color;
}