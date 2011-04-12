/*
 *  File.h
 *  
 *
 *  Created by Donald House on 2/18/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */

#ifndef __MYFILE__
#define __MYFILE__

#include <cstdlib>	// standard C utility library

#define MAXLINESIZE  4096

class File{
protected:
  char *filename;	 // Name of file
  char line[MAXLINESIZE];
  int lineno;

  void stripwhite(char *line);
  bool str_pfx(char *str, char *pfx);
  bool str_sfx(char *str, char *sfx);
  void errmsg(char *msg);
  
public:
  File(char *filename = NULL);
  ~File();

  void setfilename(char *fname);
  char *getfilename();
  
  virtual int read(char *fname = NULL) = 0;
};

#endif
