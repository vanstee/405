#----------------------------------------------
#    Makefile for compiling hw2, raycast
#----------------------------------------------
#
#  Programmer: Patrick Van Stee
#  Adpoted from: Donald House
#  Date: February 9, 2011
#

CC = g++
C	= cpp
H	= h
CFLAGS   = -g `Magick++-config --cppflags`
LFLAGS   = -g `Magick++-config --ldflags`
HFILES 	= Sphere.${H} Vector.${H} Utility.${H} 
OFILES 	= Sphere.o Vector.o Utility.o
PROJECT  = raycast

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS = -framework Foundation -framework GLUT -framework OpenGL -lMagick++ -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS = -L /usr/lib64/ -lglut -lGL -lMagick++ -lm
  endif
endif

${PROJECT}:	${PROJECT}.o $(OFILES)
	${CC} $(CFLAGS) -o ${PROJECT} ${PROJECT}.o $(OFILES) $(LDFLAGS)

${PROJECT}.o: ${PROJECT}.${C} $(HFILES)
	${CC} $(CFLAGS) -c ${PROJECT}.${C}
	
Sphere.o: Sphere.${C} Sphere.${H} Vector.${H} Utility.${H}
	${CC} $(CFLAGS) -c Sphere.${C}

Vector.o: Vector.${C} Vector.${H} Utility.${H} 
	${CC} $(CFLAGS) -c Vector.${C}

Utility.o: Utility.${C} Utility.${H}
	${CC} $(CFLAGS) -c Utility.${C}

debug:
	make 'DFLAGS = /usr/lib/debug/malloc.o'

clean:
	rm *.o *~ ${PROJECT}
