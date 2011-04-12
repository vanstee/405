/*
 *  PolySurf.cpp
 *  
 *  Created by Donald House on 2/18/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */
#include <cstdlib>
#include <iostream>

#include "PolySurf.h"
#include "MakeSpace.h"

using namespace std;

PolySurf::PolySurf(){
  nverts = nnorms = nuvs = nfaces = 0;
  maxverts = maxnorms = maxuvs = maxfaces = 0;
  verts = norms = NULL;
  uvs = NULL;
  faces = NULL;

  npoints = nlines = 0;
  maxpoints = maxlines = 0;
  points = NULL;
  lines = NULL;

  ngroups = nmaterials = 0;
  maxgroups = maxmaterials = 0;
  groups = NULL;
  materials = NULL;
}

PolySurf::~PolySurf(){
  delete []verts;
  delete []norms;
  delete []uvs;
  delete []points;
  delete []faces;
  delete []lines;
  delete []groups;
  delete []materials;
}

void PolySurf::addVertex(const Vector3d &v){
  if(maxverts == nverts)
    verts = makespace <Vector3d> (maxverts, verts);
  verts[nverts++] = v;
}

void PolySurf::addNormal(const Vector3d &n){
  if(maxnorms == nnorms)
    norms = makespace <Vector3d> (maxnorms, norms);
  norms[nnorms++] = n;
}

void PolySurf::addUV(const Vector2d &u){
  if(maxuvs == nuvs)
    uvs = makespace <Vector2d> (maxuvs, uvs);
  uvs[nuvs++] = u;
}

void PolySurf::addPoint(int p){
  if(maxpoints == npoints)
    points = makespace <int> (maxpoints, points);
  points[npoints++] = p;
}

int PolySurf::newFace(int g, int m){
  if(maxfaces == nfaces)
    faces = makespace <Face> (maxfaces, faces);
  
  faces[nfaces].setGroup(g);
  faces[nfaces].setMaterial(m);
  return nfaces++;
}

void PolySurf::addFaceVert(int f, int v, int n, int u){
  faces[f].addVert(v, n, u);
}

int PolySurf::newLine(){
  if(maxlines == nlines)
    lines = makespace <Line> (maxlines, lines);
  return nlines++;
}

void PolySurf::addLinePoint(int l, int p){
  lines[l].addPoint(p);  
}

int PolySurf::setGroup(char *gname){
  for(int i = 0; i < ngroups; i++)
    if(groups[i].isNamed(gname))
      return i;

  if(maxgroups == ngroups)
    groups = makespace <Group> (maxgroups, groups);

  groups[ngroups].setName(gname);
  return ngroups++;
}

void PolySurf::addFaceGroup(int f, int g){
  if(g != -1)
    groups[g].addFace(f);
}

int PolySurf::newMaterial(char *mname){
  int idx = idxMaterial(mname);
  if(idx != -1)
    return idx;

  if(maxmaterials == nmaterials)
    materials = makespace <Material> (maxmaterials, materials);
  
  materials[nmaterials].setName(mname);
  return nmaterials++;
}

void PolySurf::setMaterialK(int m, int k, const Color &c){
  materials[m].setK(k, c);
}

void PolySurf::setMaterialTransmission(int m, const Color &c){
  materials[m].setTransmission(c);
}

void PolySurf::setMaterialAlpha(int m, double alfa){
  materials[m].setAlpha(alfa);
}

void PolySurf::setMaterialExp(int m, double spexp){
  materials[m].setExp(spexp);
}

void PolySurf::setMaterialIOR(int m, double ior){
  materials[m].setIOR(ior);
}

void PolySurf::setMaterialIllum(int m, int n){
  materials[m].setIllum(n);
}

void PolySurf::setMaterialMap(int m, int mtype, Pixmap *p){
  materials[m].setMap(mtype, p); 
}

int PolySurf::idxMaterial(char *mname){
  for(int i = 0; i < nmaterials; i++)
    if(materials[i].isNamed(mname))
      return i;
  return -1;
}

void PolySurf::addFaceMaterial(int f, int m){
  faces[f].setMaterial(m);
}

Vector3d PolySurf::Centroid(){
  Vector3d c;
  for(int i = 0; i < nverts; i++)
    c = c + verts[i];
  c = c / nverts;
  return c;
}

Vector3d PolySurf::MinBBox(){
  Vector3d min;
  if(nverts > 0){
    min = verts[0];
    for(int i = 1; i < nverts; i++)
      for(int j = 0; j < 3; j++){
	if(verts[i][j] < min[j])
	  min[j] = verts[i][j];
      }
  }
  return min;
}

Vector3d PolySurf::MaxBBox(){
  Vector3d max;
  if(nverts > 0){
    max = verts[0];
    for(int i = 1; i < nverts; i++)
      for(int j = 0; j < 3; j++){
	if(verts[i][j] > max[j])
	  max[j] = verts[i][j];
      }
  }
  return max;
}

ostream& operator<< (ostream& os, const PolySurf& ps){
  os << "[polysurf: " << endl;
  os << "verts (" << ps.nverts << ") = ";
  for(int i = 0; i < ps.nverts; i++)
    os << ps.verts[i] << " ";
  os << endl;
  os << "faces (" << ps.nfaces << ") = " << endl;
  for(int i = 0; i < ps.nfaces; i++)
    os << i << " : " << ps.faces[i] << endl;
  os << "lines (" << ps.nlines << ") = " << endl;
  for(int i = 0; i < ps.nlines; i++)
    os << i << " : " << ps.lines[i] << endl;
  os << "points (" << ps.npoints << ") = ";
  for(int i = 0; i < ps.npoints; i++)
    os << "(" << i << " : " << ps.points[i] << ") ";
  os << endl;
  os << "groups (" << ps.ngroups << ") = " << endl;
  for(int i = 0; i < ps.ngroups; i++)
    os << i << " : " << ps.groups[i] << endl;
  os << "materials (" << ps.nmaterials << ") = " << endl;
  for(int i = 0; i < ps.nmaterials; i++)
    os << i << " : " << ps.materials[i] << endl;
  os << "]";
  return os;
}
