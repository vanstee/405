//----------------------------------------------
//    Example Program Demonstrating some of the
//    features of the Vector classes
//----------------------------------------------
//
//  Programmer: Donald House
//  Date: January 5, 2011
//
//  Copyright (C) - Donald H. House. 2011
//

#include "Vector.h"

int main(){
  Vector3d b(-3, 1.5, 1.5);
  Vector3d a(0.5, 2.9, 0.2);
  Vector3d c(0, 0, 1);
  float s = 0.7;
  Vector3d d, e, f, g;
  
  Vector3d z = a - b;
  float dist = z.norm();
  g = -z.normalize();
  e = (c % g).normalize();
  f = g % e;
  
  d = b - s * g;
  
  cout << "dist = " << dist << endl;
  cout << "z = " << z << endl;
  cout << "d = " << d << endl;
  cout << "e = " << e << ", f = " << f << ", g = " << g << endl;
  cout << endl;
  
  Vector2d p(-1, 6);
  Vector2d e0(2, -5);
  Vector2d s0(3, -1), s1(-1, 3);
  Vector2d x(-2, 3);
  
  Vector2d l = (x - p).normalize();
  Vector2d v = (x - e0).normalize();
  Vector2d t = (s0 - s1).normalize();
  Vector2d n(-t.y, t.x);

  cout << "l = " << l << endl;
  cout << "v = " << v << endl;
  cout << "t = " << t << endl;
  cout << "n = " << n << endl;
  
  float cl = -n * l;
  cout << "cl = " << cl << endl;
  
  Vector2d lr = l - 2 * (n * l) * n;
  cout << "lr = " << lr << endl;
  
  return 0; 
}
