/*
 *  Face.cpp
 *  
 *
 *  Created by Donald House on 2/18/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */
#include <cstdlib>
#include <iostream>

#include "Face.h"

using namespace std;

Face::Face(int g, int m){
  nverts = maxverts = 0; 
  verts = NULL; 
  group = g; 
  material = m;
}

void Face::setGroup(int g){
  group = g;
}

void Face::setMaterial(int m){
  material = m;
}

void Face::addVert(int v, int n, int u){
  if(maxverts == 0){
    maxverts = 3;
    verts = new int[maxverts][3];
  }
  else if(maxverts == nverts){
    int (*newverts)[3];
    newverts = new int[2 * maxverts][3];
    for(int i = 0; i < maxverts; i++){
      newverts[i][0] = verts[i][0];
      newverts[i][1] = verts[i][1];
      newverts[i][2] = verts[i][2];
    }
    delete []verts;
    verts = newverts;
    maxverts = 2 * maxverts;    
  }

  verts[nverts][0] = v;
  verts[nverts][1] = n;
  verts[nverts][2] = u;
  nverts++;
}

ostream& operator<< (ostream& os, const Face& f){
  os << "[face: (" << f.nverts << ")";
  for(int i = 0; i < f.nverts; i++)
    os << " (" << f.verts[i][0] << ", " << f.verts[i][1] << ", " << f.verts[i][2] << ")";
  os << ", group: " << f.group << ", material: " << f.material;
  os << "]";
  return os;
}
