#ifndef _H_Color
#define _H_Color

#include <Magick++.h>
using namespace std;

class Color;

class Color {
	public:
		double r, g, b;
		Color(double, double, double);
		Magick::ColorRGB ColorRGB();
		friend Color operator*(const Color&, double);
		friend Color operator*(double, const Color&);		
		friend Color operator+(const Color&, const Color&);
		friend Color operator*(const Color&, const Color&);
};

#endif
