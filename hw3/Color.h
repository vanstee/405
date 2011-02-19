#ifndef _H_Color
#define _H_Color

using namespace std;

class Color;

class Color {
	public:
		double r, g, b, a;
		Color();
		Color(double, double, double);
		Color(double, double, double, double);
		Color(const Color&);
		~Color();
		Color scale(double);
		Color add(Color);		
		Color multiply(Color);		
};

#endif
