/*
 *  PolySurf.h
 *  
 *
 *  Created by Donald House on 2/18/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */

#ifndef __POLYSURF__
#define __POLYSURF__

#include "Vector.h"
#include "Face.h"
#include "Line.h"
#include "Group.h"
#include "Material.h"

class PolySurf{
private:
  int nverts, maxverts;
  Vector3d *verts;
  int nnorms, maxnorms;
  Vector3d *norms;
  int nuvs, maxuvs;
  Vector2d *uvs;
  int npoints, maxpoints;
  int *points;
  int nfaces, maxfaces;
  Face *faces;
  int nlines, maxlines;
  Line *lines;
  int ngroups, maxgroups;
  Group *groups;
  int nmaterials, maxmaterials;
  Material *materials;

public:
  PolySurf();
  ~PolySurf();
  
  void addVertex(const Vector3d &v);
  void addNormal(const Vector3d &n);
  void addUV(const Vector2d &u);

  void addPoint(int p);

  int newFace(int g, int m);
  void addFaceVert(int f, int v, int n = -1, int u = -1);

  int newLine();
  void addLinePoint(int l, int p);
  
  int setGroup(char *gname);
  void addFaceGroup(int f, int g);
  
  int newMaterial(char *mname);
  int idxMaterial(char *mname);

  void setMaterialK(int m, int k, const Color &c);
  void setMaterialTransmission(int m, const Color &c);
  void setMaterialAlpha(int m, double alfa);
  void setMaterialExp(int m, double spexp);
  void setMaterialIOR(int m, double ior);
  void setMaterialIllum(int m, int n);
  void setMaterialMap(int m, int mtype, Pixmap *p);

  void addFaceMaterial(int f, int m);

  Vector3d Centroid();
  Vector3d MinBBox();
  Vector3d MaxBBox();
  
  void DrawPoints();
  void Draw(int wireframe);
  
  friend ostream& operator<< (ostream& os, const PolySurf& ps);
};

#endif
