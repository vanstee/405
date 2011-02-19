#include "Color.h"

using namespace std;

Color::Color(): r(0), g(0), b(0) {}

Color::Color(double r, double g, double b):
	r(r), g(g), b(b) {}
	
Color::Color(const Color& color):
 	r(color.r), g(color.g), b(color.b) {}

Color::~Color() {}

Color Color::scale(double d) {
	double r = this->r * d;
	double g = this->g * d;
	double b = this->b * d;			
	return Color(r, g, b);
}

Color Color::add(Color color) {
	double r = this->r + color.r;
	double g = this->g + color.g;
	double b = this->b + color.b;
	return Color(r, g, b);
}

Color Color::multiply(Color color) {
	double r = this->r * color.r;
	double g = this->g * color.g;
	double b = this->b * color.b;
	return Color(r, g, b);
}