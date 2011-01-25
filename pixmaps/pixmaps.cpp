/*
 *  pixmaps.cpp
 *  
 *  Demonstration of various ways to build a pixmap
 *
 *  Created by Donald House on 8/25/08.
 *  Copyright 2008 Clemson University. All rights reserved.
 *
 */

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

// handy typedefs for grey and RGBA pixels
typedef unsigned char Greypixel;
typedef unsigned char RGBApixel[4];

// globals for 3 different kinds of pixmap
Greypixel *greymap1d;
Greypixel **greymap2d;
RGBApixel **pixmap2d;

int Width, Height;

//
// drawing callback routine. Uncomment the line to draw the pixmap you want
//
void drawScreen(){
  glRasterPos2i(0, 0);
  
  //glDrawPixels(Width, Height, GL_LUMINANCE, GL_UNSIGNED_BYTE, greymap1d);
  //glDrawPixels(Width, Height, GL_LUMINANCE, GL_UNSIGNED_BYTE, greymap2d[0]);
  glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, pixmap2d[0]);

  glFlush();
}

//
//  Open window and start up glut/OpenGL graphics
//
void startgraphics(int width, int height){
  
  // open window and establish coordinate system on it
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(width, height);
  glutCreateWindow("Pixmap Demo");
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width, 0, height);
}

int main(int argc, char *argv[]){
  int row, col;

  // get image width and height from command line
  // or error if command line parameters missing
  if(argc != 3){
    cout << "usage: pixmaps w h" << endl;
    return(1);
  }
  Width = atoi(argv[1]);
  Height = atoi(argv[2]);
  
  greymap1d = new Greypixel[Width * Height];
  
  greymap2d = new Greypixel*[Height];
  greymap2d[0] = new Greypixel[Width * Height];
  for(row = 1; row < Height; row++)
    greymap2d[row] = greymap2d[row - 1] + Width;
  
  pixmap2d = new RGBApixel*[Height];
  pixmap2d[0] = new RGBApixel[Width * Height];
  for(row = 1; row < Height; row++)
    pixmap2d[row] = pixmap2d[row - 1] + Width;
  
  // make checkerboards: grey and red: 
  //   if row + col is odd, then black, else grey or red
  for(row = 0; row < Height; row++)
    for(col = 0; col < Width; col++)
      if((row / 8 + col / 8) % 2){
	greymap1d[Width * row + col] = 0;
	greymap2d[row][col] = 0;
	pixmap2d[row][col][0] = 0; pixmap2d[row][col][1] = 0;
	pixmap2d[row][col][2] = 0; pixmap2d[row][col][3] = 255;
      }
      else{
	greymap1d[Width * row + col] = 255;
	greymap2d[row][col] = 255;
	pixmap2d[row][col][0] = 255; pixmap2d[row][col][1] = 0;
	pixmap2d[row][col][2] = 0; pixmap2d[row][col][3] = 255;
      }
	
  // start up glut
  glutInit(&argc, argv);
  
  // open window and establish coordinate system on it
  startgraphics(Width, Height);
  
  // register display and mouse-button callback routines
  glutDisplayFunc(drawScreen);
  glutMainLoop();
  
  return 0;
}

