/*
 *  Pixmap.h
 *  
 *  Pixmap class for general use in handling RGBA colors
 *  Sample solution for CP SC 405/605
 *
 *  Created by Donald House on 9/8/08.
 *  Copyright 2008 Clemson University. All rights reserved.
 *
 */

#ifndef _PIXMAP_H_
#define _PIXMAP_H_

//
// A single RGBA pixel. 
//
struct RGBAPixel{
  unsigned char r, g, b, a;	// colors stored as .r, .g, .b, .a
  
  unsigned char &operator[](int i); // colors can be accesed as array
};

//
// A single row in an RGBA pixmap. Used only for double indexing [][]
//
struct Pixrow{
  RGBAPixel *px;
  
  RGBAPixel &operator[](int c);
};

//
// The pixmap itself
//
class Pixmap{
private:
  Pixrow *rows;
  int nrows, ncols;
  
  void deallocate();
  
public:
  // constructor and destructor
  Pixmap(int r = 0, int c = 0);
  ~Pixmap();
  
  // allocate memory and record size
  void SetSize(int r, int c);
  int NRows() {return nrows;};
  int NCols() {return ncols;};
  
  // returns a pointer to the pixmap's data block in memory
  unsigned char *Pixels(){return (unsigned char *)rows[0].px;};

  // The pixmap can be indexed. The first index returns the row.
  // The second index returns the pixel in the row at the column.
  Pixrow &operator[](int r);
  
  void Draw();
};

#endif

