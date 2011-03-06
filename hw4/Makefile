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
HFILES 	= Camera.${H} ParallelLight.${H} PointLight.${H} Light.${H} Sphere.${H} Material.${H} Color.${H} Vector.${H} Utility.${H} 
OFILES 	= Camera.o ParallelLight.o PointLight.o Light.o Sphere.o Material.o Color.o Vector.o Utility.o
PROJECT  = raytrace

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

Camera.o: Camera.${C} Camera.${H} Vector.${H} Utility.${H}
	${CC} $(CFLAGS) -c Camera.${C}

ParallelLight.o: ParallelLight.${C} ParallelLight.${H} Light.${H} Vector.${H} Utility.${H} Color.${H}
	${CC} $(CFLAGS) -c ParallelLight.${C}

PointLight.o: PointLight.${C} PointLight.${H} Light.${H} Vector.${H} Utility.${H} Color.${H}
	${CC} $(CFLAGS) -c PointLight.${C}

Light.o: Light.${C} Light.${H} Vector.${H} Utility.${H} Color.${H}
	${CC} $(CFLAGS) -c Light.${C}	

Sphere.o: Sphere.${C} Sphere.${H} Vector.${H} Utility.${H} Material.${H}
	${CC} $(CFLAGS) -c Sphere.${C}

Material.o: Material.${C} Material.${H} Material.${H}
	${CC} $(CFLAGS) -c Material.${C}
	
Color.o: Color.${C} Color.${H}
	${CC} $(CFLAGS) -c Color.${C}	
	
Vector.o: Vector.${C} Vector.${H} Utility.${H} 
	${CC} $(CFLAGS) -c Vector.${C}

Utility.o: Utility.${C} Utility.${H}
	${CC} $(CFLAGS) -c Utility.${C}

debug:
	make 'DFLAGS = /usr/lib/debug/malloc.o'

clean:
	rm *.o *~ ${PROJECT}
