/*
 *  Line.h
 *  
 *
 *  Created by Don House on 3/30/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __MYLINE__
#define __MYLINE__

#include <iostream>
#include "Vector.h"

struct Line{
  int npoints, maxpoints;
  int *points;
  
  Line(){npoints = 0; maxpoints = 0; points = NULL;}
  ~Line(){;}   // note, points not destroyed
  
  void addPoint(int p);
  
  friend ostream& operator<< (ostream& os, const Line& l);
};

#endif
