//
// Definitions for class to read/write Images using Magick++
//
// CPSC 405/605 Donald H. House 2/17/2011
//
//

#ifndef _IMAGEFILE
#define _IMAGEFILE

#include "File.h"
#include "Pixmap.h"
#include <Magick++.h>

// Image file structure
class ImageFile: public File{
private:
  Pixmap *pixmap;	 // RGBA pixmap

public:
  ImageFile(char *filename = NULL);
  ~ImageFile(){};
  
  void setpixmap(Pixmap *p);
  Pixmap *getpixmap();

  int getwidth();
  int getheight();
    
  int read(char *fname = NULL);

  void write();
  void write(char *fname);
};

#endif
