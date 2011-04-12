/*
 *  Line.cpp
 *  
 *
 *  Created by Don House on 3/30/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Line.h"
#include "MakeSpace.h"

using namespace std;

void Line::addPoint(int p){
  if(maxpoints == npoints)
    points = makespace <int> (maxpoints, points);
  points[npoints++] = p;
}

ostream& operator<< (ostream& os, const Line& l){
  os << "[line: (" << l.npoints << ")";
  for(int i = 0; i < l.npoints; i++)
    os << ", " << l.points[i];
  os << "]";
  return os;
}
