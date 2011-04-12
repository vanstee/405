/*
 *  Color.h
 *  
 *
 *  Created by Donald House on 9/24/08.
 *  Copyright 2008 Clemson University. All rights reserved.
 *
 */

#ifndef _COLOR_H_
#define _COLOR_H_

#include <iostream>
using namespace std;

class Color{
public:
  float r, g, b, a;	// colors stored as .r, .g, .b, .a
  
  Color(float r0 = 0, float g0 = 0, float b0 = 0, float a0 = 1);
  Color(const Color &c);
  
  void set(const Color &c);
  void set(float r0 = 0, float g0 = 0, float b0 = 0, float a0 = 1);
  
  float *glcolor();	// pointer to an array of 3
  
  float &operator[](int i); // colors can also be accesed as array
  
  const Color &operator=(const Color &c);
  
  Color operator+(const Color &c);
  Color operator*(const Color &c);
  Color operator*(float s);
  Color operator/(float s);
  friend Color operator*(float s, const Color &c);
  friend ostream& operator<< (ostream& os, const Color& c);
};

#endif
