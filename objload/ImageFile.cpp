//
// Class to read/write Images using Magick++
//
// CPSC 405/605 Donald H. House 2/17/2011
//
//

#include <iostream>	// C++ I/O
#include <cstdlib>	// standard C utility library

#include "ImageFile.h"

using namespace std;
using namespace Magick;

//****************** ImageFile Routines **********************

ImageFile::ImageFile(char *fname){
  pixmap = NULL;

  filename = NULL;
  setfilename(fname);
  if(filename != NULL) 
    read(fname);
}

void ImageFile::setpixmap(Pixmap *p){
  pixmap = p;
}

Pixmap *ImageFile::getpixmap(){
  return pixmap;
}

int ImageFile::getwidth(){
  if(pixmap == NULL)
    return 0;
  else
    return pixmap->NCols();
}

int ImageFile::getheight(){
  if(pixmap == NULL)
    return 0;
  else
    return pixmap->NRows();
}

//
// Routine to read an image file using Magick++ and copy the image to a newly
// created pixmap. Returns the size of the image read, or 0 image read failed
//
int ImageFile::read(char *fname){
  int imwidth, imheight;

  setfilename(fname);

  if(filename == NULL){
    cout << "No filename specified for reading image file." << endl;
    return 0;
  }

  // use Magick++ to load the image based on the filename and extension
  Image image;
  try{
    image.read(filename);
  }
  catch(Error& error){	  // bomb out if error reading image
    cout << "Error reading image file: " << error.what() << endl;
    return 0;
  }
  
  // Magick++ treats upper left corner of image as its origin, while
  // OpenGL treats the lower left corner as its origin.
  image.flip();
  
  // Record image width and height in global variables for easy access
  imwidth = image.columns();
  imheight = image.rows();
  
  // make a new pixmap of the new size
  pixmap = new Pixmap(imheight, imwidth);
  
  // fetch the pixmap from the Magick++ Image
  image.write(0, 0, imwidth, imheight, "RGBA", CharPixel, (void *)pixmap->Pixels());
  
  // returns image size in pixels
  return imwidth * imheight;
}

//
// Routine to write the current pixmap contents to an image file using Magick++
//
void ImageFile::write(char *fname){

  setfilename(fname);
  
  if(filename == NULL)
    return;
  
  // Create a Magick++ image and pass it the pixmap
  Image image(getwidth(), getheight(), "RGBA", CharPixel, (void *)pixmap->Pixels());
  
  // Magick++ treats upper left corner of image as its origin, while
  // OpenGL treats the lower left corner as its origin.
  image.flip();
  
  // Write the image out to the named image file
  try{
    image.write(filename);
  }
  catch(Error& error){
    cout << "Error writing image file: " << error.what() << endl;
  }
}
