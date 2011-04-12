/*
 *  File.cpp
 *  
 *
 *  Created by Donald House on 2/18/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */

#include "File.h"

#include <cstdio>
#include <iostream>	// C++ I/O

using namespace std;

//
// helper functions for working with strings ************************************
//
void File::stripwhite(char *line){
  int i, j;
  
  for(i = 0; i < strlen(line) && isspace(line[i]); i++);
  for(j = 0; i < strlen(line); i++){
    if(!isspace(line[i]) || (strlen(line) > i + 1 && !isspace(line[i + 1])))
      line[j++] = line[i];
  }
  line[j] = '\0';
}

bool File::str_pfx(char *str, char *pfx){
  if(pfx == NULL)
    return true;
  if(str == NULL)
    return false;
  if(strlen(str) < strlen(pfx))
    return false;
  
  for(int i = 0; i < strlen(pfx); i++)
    if(str[i] != pfx[i])
      return false;
  
  return true;
}

bool File::str_sfx(char *str, char *sfx){
  int i, j;
  
  if(sfx == NULL)
    return true;
  if(str == NULL)
    return false;
  if(strlen(str) < strlen(sfx))
    return false;
  
  for(i = strlen(sfx) - 1, j = strlen(str) - 1; i >= 0; i--, j--)
    if(str[j] != sfx[i])
      return false;

  return true;
}

void File::errmsg(char *msg){
  cerr << filename << ": " << msg << ", on line  " << lineno << ": " << line << endl;
}

//
// end of helper functions for working with strings ******************************
//

File::File(char *fname){
  filename = NULL;
  setfilename(fname);

  lineno = 0;
}

File::~File(){
  delete filename;
}

void File::setfilename(char *fname){
  delete filename;
  if(fname == NULL)
    filename = NULL;
  else{
    filename = new char[strlen(fname) + 1];
    strcpy(filename, fname);
  }
}

char *File::getfilename(){
  char *rname;
  
  if(filename == NULL)
    return NULL;
  
  rname = new char[strlen(filename) + 1];
  strcpy(rname, filename);
  return rname;
}
