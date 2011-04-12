/*
 *  MakeSpace.h
 *  
 *
 *  Created by Don House on 3/30/11.
 *  Copyright 2011 Clemson University. All rights reserved.
 *
 */

#ifndef __MAKESPACE__
#define __MAKESPACE__

template <class arraytype> 
arraytype *makespace(int &max, arraytype array[]){
  arraytype *newarray;
  
  if(max == 0){
    max = 3;
    newarray = new arraytype[max];
  }
  else{
    newarray = new arraytype[2 * max];
    for(int i = 0; i < max; i++)
      newarray[i] = array[i];
    delete []array;
    max = 2 * max;
  }
  
  return newarray;
}

#endif

