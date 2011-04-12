/*
 *  MTLFile.h
 *  
 *
 *  Created by Donald House on 2/18/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */

#ifndef __MTLFILE__
#define __MTLFILE__

#include "File.h"
#include "PolySurf.h"

class MTLFile: public File{
private:
  PolySurf *psurf;
  int materialno;

  int processnewmtl(char *line);
  int processK(char *line);
  int processTf(char * line);
  int processN(char * line);
  int processd(char * line);
  int processillum(char * line);
  int processmap(char * line);
  
public:
  MTLFile(PolySurf *ps = NULL, char *filename = NULL);
  ~MTLFile();
  
  void setPSurf(PolySurf *ps);
  PolySurf *getPSurf();
  
  int read(char *fname = NULL);
};

#endif
