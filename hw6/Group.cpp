/*
 *  Group.cpp
 *  
 *
 *  Created by Don House on 3/30/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */

#include "Group.h"
#include "MakeSpace.h"

using namespace std;

Group::Group(char *gname){
  nfaces = maxfaces = 0;
  faces = NULL;
  
  name = NULL;
  setName(gname);
}

void Group::setName(char *gname){
  delete []name;
  if(gname == NULL || strlen(gname) == 0)
    name = NULL;
  else{
    name = new char[strlen(gname) + 1];
    strcpy(name, gname);
  }
}

bool Group::isNamed(char *gname){
  if(name == NULL || gname == NULL)
    return false;
  return strcmp(gname, name) == 0;
}

void Group::addFace(int f){
  if(maxfaces == nfaces)
    faces = makespace <int> (maxfaces, faces);
  
  faces[nfaces++] = f;
}

ostream& operator<< (ostream& os, const Group& g){
  os << "[group " << g.name << ": (" << g.nfaces << ")";
  for(int i = 0; i < g.nfaces; i++)
    os << ", " << g.faces[i];
  os << "]";
  return os;
}
