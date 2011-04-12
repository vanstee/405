/*
 *  OBJFile.h
 *  
 *
 *  Created by Donald House on 2/18/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */

#ifndef __OBJFILE__
#define __OBJFILE__

#include "File.h"
#include "PolySurf.h"

class OBJFile: public File{
private:
  PolySurf *psurf;
  int groupno;
  int materialno;

  int processvn(char *line);
  int processvt(char *line);
  
  int processv(char *line);
  int processp(char *line);
  int processl(char *line);
  int processf(char *line);
  
  int processg(char * line);
  int processmtllib(char * line);
  int processusemtl(char * line);
  
public:
  OBJFile(char *filename = NULL);
  ~OBJFile();

  int read(char *fname = NULL);
  PolySurf *getscene();
};

#endif
