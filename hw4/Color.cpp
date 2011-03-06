#include "Color.h"

using namespace std;

Color::Color(double r, double g, double b):
	r(r), g(g), b(b) {}
	
Magick::ColorRGB Color::ColorRGB() {
	double r = this->r;
	double g = this->g;
	double b = this->b;
	
	r = r < 0 ? 0 : r;
	g = g < 0 ? 0 : g;
	b = b < 0 ? 0 : b;
	
	r = r > 1 ? 1 : r;
	g = g > 1 ? 1 : g;
	b = b > 1 ? 1 : b;			
				
	return Magick::ColorRGB(r, g, b);
}

Color operator*(const Color& color, double scalar) {
	double r = color.r * scalar;
	double g = color.g * scalar;
	double b = color.b * scalar;
	return Color(r, g, b);		
}

Color operator*(double scalar, const Color& color) {
	double r = color.r * scalar;
	double g = color.g * scalar;
	double b = color.b * scalar;
	return Color(r, g, b);
}

Color operator+(const Color& color1, const Color& color2) {
	double r = color1.r + color2.r;
	double g = color1.g + color2.g;
	double b = color1.b + color2.b;
	return Color(r, g, b);		
}

Color operator*(const Color& color1, const Color& color2) {
	double r = color1.r * color2.r;
	double g = color1.g * color2.g;
	double b = color1.b * color2.b;
	return Color(r, g, b);		
}
