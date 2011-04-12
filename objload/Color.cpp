/*
 *  Color.cpp
 *  
 *
 *  Created by Donald House on 9/24/08.
 *  Copyright 2008 Clemson University. All rights reserved.
 *
 */

#include "Color.h"

Color::Color(float r0, float g0, float b0, float a0){
  set(r0, g0, b0, a0);
}

Color::Color(const Color &c){
  set(c);  
}

void Color::set(const Color &c){
  set(c.r, c.g, c.b, c.a);
}

void Color::set(float r0, float g0, float b0, float a0){
  r = r0;
  g = g0;
  b = b0;
  a = a0;  
}

const Color &Color::operator=(const Color &c){
  r = c.r;
  g = c.g;
  b = c.b;
  a = c.a;
  
  return *this;
}

float *Color::glcolor(){
  return &r;
}

float &Color::operator[](int i){ // colors can be accesed as array
  switch(i){
  case 0:
    return r;
    break;
  case 1:
    return g;
    break;
  case 2:
    return b;
    break;
  case 3:
  default:
    return a;
    break;
  }
}

Color Color::operator+(const Color &c){
  Color rc;
  
  rc.r = r + c.r;
  rc.g = g + c.g;
  rc.b = b + c.b;
  rc.a = a + c.a;
  
  return rc;
}

Color Color::operator*(const Color &c){
  Color rc;
  
  rc.r = r * c.r;
  rc.g = g * c.g;
  rc.b = b * c.b;
  rc.a = a * c.a;
  
  return rc;  
}

Color Color::operator*(float s){
  Color rc;
  
  rc.r = s * r;
  rc.g = s * g;
  rc.b = s * b;
  rc.a = s * a;
  
  return rc;  
}

Color Color::operator/(float s){
  Color rc;
  
  rc.r = r / s;
  rc.g = g / s;
  rc.b = b / s;
  rc.a = a / s;
  
  return rc;  
}

Color operator*(float s, const Color &c){
  Color rc;
  
  rc.r = s * c.r;
  rc.g = s * c.g;
  rc.b = s * c.b;
  rc.a = s * c.a;
  
  return rc;  
}

ostream& operator<< (ostream& os, const Color& c){
  os << "(" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
  return os;
}
