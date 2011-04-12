/*
 *  MTLFile.cpp
 *  
 *
 *  Created by Donald House on 2/18/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */

#include "MTLFile.h"
#include "ImageFile.h"
#include <cstdio>
#include <iostream>	// C++ I/O
#include <cstdlib>	// standard C utility library

//
// end of helper functions for working with strings ******************************
//

MTLFile::MTLFile(PolySurf *ps, char *fname): File(fname){
  psurf = NULL;
  setPSurf(ps);

  if(filename != NULL)
    read();
}

MTLFile::~MTLFile(){
}

void MTLFile::setPSurf(PolySurf *ps){
  psurf = ps;
}

PolySurf *MTLFile::getPSurf(){
  return psurf;
}

int MTLFile::read(char *fname){
  FILE *infile;
  int err;
  
  if(psurf == NULL){
    errmsg("Cannot read MTL file, no polygonal surface given");
    return 1;    
  }
  
  if(fname != NULL)
    setfilename(fname);
  
  if(filename == NULL){
    errmsg("Cannot open OBJ file, no filename given");
    return 2;
  }
  
  infile = fopen(filename, "r");
  if(infile == NULL){
    errmsg("Cannot open MTL file");
    return 3;
  }
  
  lineno = 0;
  while(fgets(line, MAXLINESIZE, infile) != NULL){
    lineno++;
    stripwhite(line);
    if(strlen(line) == 0 || line[0] == '#')
      continue;
    
    switch(line[0]){
      case 'n':
	err = processnewmtl(line);
	break;
      case 'K':
	err = processK(line);
	break;
      case 'T':
	err = processTf(line);
	break;
      case 'N':
	err = processN(line);
	break;
      case 'd':
	err = processd(line);
	break;
      case 'i':
	err = processillum(line);
	break;
      case 'm':
	err = processmap(line);
	break;
      default:
	errmsg("Invalid line type");
	err = 100;
    }
  }
  
  return err;
}

int MTLFile::processnewmtl(char *line){
  int nfields;
  char mtlname[256];

  if(strlen(line) < 8 || !isspace(line[6]) || !str_pfx(line, "newmtl")){  // newmtl m
    errmsg("Invalid material name format");
    return 1;
  }
  
  nfields = sscanf(line, "newmtl %s", mtlname);
  if(nfields != 1){
    errmsg("Invalid material name");
    return 2;
  }

  materialno = psurf->newMaterial(mtlname);
  return 0;
}

int MTLFile::processK(char *line){
  int nfields;
  int ktype;
  Color kcolor;
  char junk[2];

  if(strlen(line) < 8 || !isspace(line[2])){	  // Kx r g b
    errmsg("Invalid K format");
    return 1;
  }
  
  switch(line[1]){
  case 'a':
      ktype = 0;
    break;
  case 'd':
      ktype = 1;
    break;
  case 's':
      ktype = 2;
    break;
  default:
    errmsg("Invalid K type");
    return 2;
  }
  
  nfields = sscanf(line, "%s %f %f %f", junk, &(kcolor.r), &(kcolor.g), &(kcolor.b));
  if(nfields != 4){
    errmsg("Invalid K value");
    return 2;
  }
  kcolor.a = 1.0;
  psurf->setMaterialK(materialno, ktype, kcolor);
  return 0;
}

int MTLFile::processTf(char *line){
  int nfields;
  Color tcolor;
  
  if(strlen(line) < 8 || !isspace(line[2])){	  // Tf r g b
    errmsg("Invalid Tf format");
    return 1;
  }
  
  nfields = sscanf(line, "Tf %f %f %f", &(tcolor.r), &(tcolor.g), &(tcolor.b));
  if(nfields != 4){
    errmsg("Invalid Tf value");
    return 2;
  }
  tcolor.a = 1.0;
  
  psurf->setMaterialTransmission(materialno, tcolor);
  return 0;
}

int MTLFile::processd(char *line){
  int nfields;
  double dissolve;
  
  if(strlen(line) < 3 || line[1] != ' '){	  // d f
    errmsg("Invalid d format");
    return 1;
  }
  
  nfields = sscanf(line, "d %lf", &dissolve);
  if(nfields != 1 || dissolve < 0.0 || dissolve > 1.0){
    errmsg("Invalid d value");
    return 2;
  }
  
  psurf->setMaterialAlpha(materialno, dissolve);
  return 0;
}

int MTLFile::processN(char *line){
  int nfields;
  int ntype;
  char junk[2];
  double nvalue;
  
  if(strlen(line) < 4 || !isspace(line[2])){	  // Nx e
    errmsg("Invalid N format");
    return 1;
  }

  switch(line[1]){
    case 's':
      ntype = 0;
      break;
    case 'i':
      ntype = 1;
      break;
    default:
      errmsg("Invalid N type");
      return 2;
  }
  
  nfields = sscanf(line, "%s %lf", junk, &nvalue);
  if(nfields != 2 || nvalue < 0){
    errmsg("Invalid N value, on line number");
    return 2;
  }
  
  if(ntype == 0)
    psurf->setMaterialExp(materialno, nvalue);
  else
    psurf->setMaterialIOR(materialno, nvalue);
  return 0;
}

int MTLFile::processillum(char *line){
  int nfields;
  int n;
  
  if(strlen(line) < 7 || !isspace(line[5])){	  // illum n
    errmsg("Invalid illum format");
    return 1;
  }
  
  nfields = sscanf(line, "illum %d", &n);
  if(nfields != 1 || n < 0 || n > 2){
    errmsg("Invalid illum value");
    return 2;
  }
  
  psurf->setMaterialIllum(materialno, n);
  return 0;
}

int MTLFile::processmap(char *line){
  int nfields, imsize;
  char imfilename[256];
  char junk[6];
  ImageFile imfile;
  int mtype;

  if(strlen(line) < 12 || !isspace(line[6]) || !str_pfx(line, "map_K")){	  // map_Kx n.png
    errmsg("Invalid map format, on line number");
    return 1;
  }

  switch(line[5]){
    case 'a':
      mtype = 0;
      break;
    case 'd':
      mtype = 1;
      break;
    case 's':
      mtype = 2;
      break;
    default:
      errmsg("Invalid map type, on line number");
      return 2;
  }
  
  nfields = sscanf(line, "%s %s", junk, imfilename);
  if(nfields != 2){
    errmsg("Invalid map filename, on line number");
    return 2;
  }
  
  imsize = imfile.read(imfilename);
  if(imsize == 0){
    errmsg("Could not read map file");
    return 3;
  }

  psurf->setMaterialMap(materialno, mtype, imfile.getpixmap());
  return 0;  
}
