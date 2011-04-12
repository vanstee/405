/*
 *  OBJFile.cpp
 *  
 *
 *  Created by Donald House on 2/18/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */

#include "OBJFile.h"
#include "MTLFile.h"
#include <cstdio>
#include <iostream>	// C++ I/O
#include <cstdlib>	// standard C utility library

OBJFile::OBJFile(char *fname): File(fname){

  psurf = NULL;
  lineno = 0;
  groupno = materialno = -1;
  
  if(filename != NULL)
    read();
}

OBJFile::~OBJFile(){
}

int OBJFile::read(char *fname){
  FILE *infile;
  char newline[MAXLINESIZE];
  int err;
  
  if(fname != NULL)
    setfilename(fname);
  
  if(filename == NULL){
    cerr << "Cannot open OBJ file, no filename given" << endl;
    return 1;
  }
  
  infile = fopen(filename, "r");
  if(infile == NULL){
    cerr << "Cannot open OBJ file " << filename << endl;
    return 2;
  }
  
  psurf = new PolySurf;
  lineno = 0;
  while(fgets(line, MAXLINESIZE, infile) != NULL){
    lineno++;
    stripwhite(line);
    if(strlen(line) == 0 || line[0] == '#')
      continue;
    while(line[strlen(line) - 1] == '\\'){
      line[strlen(line) - 1] = ' ';
      fgets(newline, MAXLINESIZE, infile);
      lineno++;
      stripwhite(newline);
      strcat(line, newline);
    }

    switch(line[0]){
      case 'v':
	err = processv(line);
	break;
      case 'p':
	err = processp(line);
	break;
      case 'l':
	err = processl(line);
	break;
      case 'f':
	err = processf(line);
	break;
      case 'g':
	err = processg(line);
	break;
      case 'm':
	err = processmtllib(line);
	break;
      case 'u':
	err = processusemtl(line);
	break;
      case 'o':
      case 's':
	errmsg("o or s line type");
	err = 0;
	break;
      default:
	errmsg("Invalid first character");
	err = 100;
    }
    if(err){
      delete psurf;
      psurf = NULL;
      return err;
    }
  }

  return 0;
}

PolySurf *OBJFile::getscene(){
  return psurf;
}


int OBJFile::processvn(char *line){
  int nfields;
  Vector3d nrm;
  
  if(strlen(line) < 8 || !isspace(line[2])){	  // vn x y z
    errmsg("Invalid normal format");
    return 1;
  }
  
  nfields = sscanf(line, "vn %lf %lf %lf", &nrm.x, &nrm.y, &nrm.z);
  if(nfields != 3){
    errmsg("Invalid normal coordinates");
    return 2;
  }
  
  psurf->addNormal(nrm);
  return 0;
}

int OBJFile::processvt(char *line){
  int nfields;
  Vector2d uv;
  
  if(strlen(line) < 6 || !isspace(line[2])){	  // vt u v
    errmsg("Invalid texture coordinate format");
    return 1;
  }
  
  nfields = sscanf(line, "vt %lf %lf", &uv.x, &uv.y);
  if(nfields != 2){
    errmsg("Invalid texture coordinates");
    return 2;
  }
  
  psurf->addUV(uv);
  return 0;
}

int OBJFile::processv(char *line){
  int nfields;
  Vector3d vtx;
  
  if(strlen(line) < 6){	  // vt u v
    errmsg("Invalid vertex format");
    return 1;
  }
  
  if(line[1] == 'n')
    return processvn(line);
  else if(line[1] == 't')
    return processvt(line);
  
  nfields = sscanf(line, "v %lf %lf %lf", &(vtx.x), &(vtx.y), &(vtx.z));
  if(nfields != 3){
    errmsg("Invalid vertex coordinates");
    return 2;
  }
  
  psurf->addVertex(vtx);
  return 0;
}

int OBJFile::processp(char *line){
  int nfields;
  int pidx;
  
  if(strlen(line) < 3 || !isspace(line[1])){	  // p n
    errmsg("Invalid point format");
    return 1;
  }
  
  nfields = sscanf(line, "p %d", &pidx);
  if(nfields != 1){
    errmsg("Invalid point index");
    return 2;
  }
  
  psurf->addPoint(pidx - 1);
  return 0;
}

int OBJFile::processl(char *line){
  int ptidx;
  int lineidx;
  
  if(strlen(line) < 3 || !isspace(line[1])){	  // l n
    errmsg("Invalid line format");
    return 1;
  }
  
  lineidx = psurf->newLine();
  ptidx = 0;
  for(int i = 1; i < strlen(line); i++){
    if(isspace(line[i])){
      if(i > 1){
	if(ptidx <= 0){
	  errmsg("Invalid point index");
	  return 3;
	}
	psurf->addLinePoint(lineidx, ptidx - 1);
      }
      ptidx = 0;
    }
    else if(!isdigit(line[i])){
      errmsg("Invalid point index");
      return 2;
    }
    else
      ptidx = 10 * ptidx + line[i] - '0';
  }
  
  if(ptidx <= 0){
    errmsg("Invalid point index");
    return 3;
  }
  
  psurf->addLinePoint(lineidx, ptidx - 1);
  return 0;
}

int OBJFile::processf(char *line){
  int idx[3];	      // vertex index, texture index, normal index
  int faceidx;

  if(strlen(line) < 7 || !isspace(line[1])){	  // f n n n
    errmsg("Invalid face format");
    return 1;
  }
  
  faceidx = psurf->newFace(groupno, materialno);
  psurf->addFaceGroup(faceidx, groupno);

  idx[0] = idx[1] = idx[2] = 0;
  for(int i = 1, j = 0; i < strlen(line); i++){
    if(isspace(line[i])){
      if(i > 1){
	if(idx[0] <= 0 || idx[1] < 0 || idx[2] < 0){
	  errmsg("Invalid vertex index");
	  return 3;
	}
	psurf->addFaceVert(faceidx, idx[0] - 1, idx[2] - 1, idx[1] - 1);
      }
      idx[0] = idx[1] = idx[2] = 0;
      j = 0;
    }
    else if(line[i] == '/'){
      j++;
      if(j > 2){
	errmsg("Invalid /");
	return 4;
      }
    }
    else if(!isdigit(line[i])){
      errmsg("Invalid index");
      return 2;
    }
    else
      idx[j] = 10 * idx[j] + line[i] - '0';
  }
  
  if(idx[0] <= 0 || idx[1] < 0 || idx[2] < 0){
    errmsg("Invalid vertex index");
    return 3;
  }

  psurf->addFaceVert(faceidx, idx[0] - 1, idx[2] - 1, idx[1] - 1);
  return 0;
}

int OBJFile::processg(char *line){
  int nfields;
  char groupname[256];
  MTLFile mtlfile;

  if(strlen(line) < 1){	  // g
    errmsg("Invalid group format");
    return 1;
  }
  
  nfields = sscanf(line, "g %s", groupname);
  if(nfields != 1 && nfields != EOF){
    errmsg("Invalid group name");
    return 2;
  }

  if(nfields == EOF)
    groupno = -1;
  else
    groupno = psurf->setGroup(groupname);
  //cout << *psurf << endl;
  return 0;
}

int OBJFile::processmtllib(char *line){
  int nfields;
  char mtlfilename[256];
  MTLFile mtlfile;
  int err;
  
  if(strlen(line) < 12 || !str_pfx(line, "mtllib") || !str_sfx(line, ".mtl")){ // mtllib m.mtl
    errmsg("Invalid mtllib format");
    return 1;
  }

  nfields = sscanf(line, "mtllib %s", mtlfilename);
  if(nfields != 1 || strlen(mtlfilename) == 0){
    errmsg("Invalid mtllib file name");
    return 2;
  }

  mtlfile.setPSurf(psurf);
  err = mtlfile.read(mtlfilename);
  if(err)
    return 3;    

  return 0;
}

int OBJFile::processusemtl(char *line){
  int nfields;
  char mtlname[256];

  if(strlen(line) < 8 || !str_pfx(line, "usemtl ")){  // usemtl m
    errmsg("Invalid usemtl format");
    return 1;
  }

  nfields = sscanf(line, "usemtl %s", mtlname);
  if(nfields != 1 || strlen(mtlname) == 0 || psurf->idxMaterial(mtlname) == -1){
    errmsg("Invalid material name");
    return 2;
  }

  materialno = psurf->idxMaterial(mtlname);
  if(materialno == -1){
    errmsg("Undefined material name");
    return 3;    
  }
  return 0;
}
