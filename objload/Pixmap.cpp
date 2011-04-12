/*
 *  Pixmap.cpp
 *  
 *  Pixmap class for general use in handling RGBA colors
 *  Sample solution for CP SC 405/605
 *
 *  Created by Donald House on 9/8/08.
 *  Copyright 2008 Clemson University. All rights reserved.
 *
 */

#include <cstdlib>
#include "Pixmap.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


using namespace std;

//
// Allow color channels in an RGBA pixel to be alternatively addressed by
// index [0] for red through [3] for alpha
//
unsigned char &RGBAPixel::operator[](int i){
  if(i == 0)
	return r;
  else if(i == 1)
	return g;
  else if(i == 2)
	return b;
  else
	return a;
}

//
// Address columns of a pixmap to be across a row
//
RGBAPixel &Pixrow::operator[](int c){
  return px[c];
}

//
// Internal method to deallocate the memory used by a pixmap
//
void Pixmap::deallocate(){
  if(rows == NULL)
	return;
  
  delete rows[0].px;
  delete []rows;
  
  rows = NULL;
}

//
// Default Pixmap constructor. Create pixmap of r x c dimensions 
// (0 x 0) by default
//
Pixmap::Pixmap(int r, int c){
  rows = NULL;
  nrows = ncols = 0;
  
  SetSize(r, c);
}

//
// Destroy a pixmap by cleaning up its space allocation
//
Pixmap::~Pixmap(){
  deallocate();
}

//
// Changing a pixmap's size. This causes any old memory to be deallocated,
// and new space allocated
//
void Pixmap::SetSize(int r, int c){
  RGBAPixel *pixels;
  
  if(nrows != r || ncols != c)
    deallocate();

  nrows = r;
  ncols = c;

  if(nrows == 0 && ncols == 0)
    return;
  
  rows = new Pixrow[nrows];
  pixels = new RGBAPixel[nrows * ncols];
  for(int row = 0; row < nrows; row++)
    rows[row].px = pixels + row * ncols;
}

//
// Address rows of a pixmap 
//
Pixrow &Pixmap::operator[](int r){
  return rows[r];
}

//
//
//
void Pixmap::Draw(){
  glDrawPixels(NCols(), NRows(), GL_RGBA, GL_UNSIGNED_BYTE, Pixels());
}
