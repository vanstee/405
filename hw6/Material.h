/*
 *  Material.h
 *  
 *
 *  Created by House on 9/8/08.
 *  Copyright 2008 Clemson University. All rights reserved.
 *
 */

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Color.h"
#include "Pixmap.h"

//
// Basic structure for storing the shading information about a surface
//
struct Material{
  char *name;
  
  Color a;
  Color d;
  Color s;
  double exp;
  double alpha;

  Color t;
  double n;

  int illum_model;

  Pixmap *amap;
  Pixmap *dmap;
  Pixmap *smap;
  
  Material(char *mname = NULL);
  Material(const Color &ambient, const Color &diffuse, const Color &specular, 
	   double spexp);

  ~Material(){};
  
  void setName(char *mname);
  bool isNamed(char *mname);

  void setProperties(const Color &ambient, const Color &diffuse, const Color &specular, 
		     double spexp);
  void setProperties(double ambient, double diffuse, double specular, 
		     double spexp);
  
  void setK(int ktype, const Color &c);
  void setTransmission(const Color &c);
  void setExp(double spexp);
  void setAlpha(double alfa);
  void setIOR(double ior);
  void setIllum(int i);
  void setMap(int mtype, Pixmap *p);
  
  friend ostream& operator<< (ostream& os, const Material& m);
};

#endif
