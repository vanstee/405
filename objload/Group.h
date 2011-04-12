/*
 *  Group.h
 *  
 *
 *  Created by Don House on 3/30/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */

#ifndef __GROUP__
#define __GROUP__

#include <iostream>

using namespace std;

struct Group{
  int nfaces, maxfaces;
  int *faces;
  char *name;
  
  Group(char *gname = NULL);
  ~Group(){};   // note, face list not destroyed
  
  void setName(char *gname);
  bool isNamed(char *gname);
  
  void addFace(int f);
  
  friend ostream& operator<< (ostream& os, const Group& g);
};

#endif
