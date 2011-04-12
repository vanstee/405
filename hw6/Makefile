CC = g++
C	= cpp
H	= h

CFLAGS		= -g `Magick++-config --cppflags`
LFLAGS		= -g `Magick++-config --ldflags`

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -lMagick++ -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -lglut -lGL -lMagick++ -lm
  endif
endif

HFILES = File.${H} OBJFile.${H} MTLFile.${H} ImageFile.${H} PolySurf.${H} Face.${H} Line.${H} Group.${H} Material.${H} Color.${H} Pixmap.${H} Vector.${H} Utility.${H} MakeSpace.${H}
OFILES = File.o OBJFile.o MTLFile.o ImageFile.o PolySurf.o Face.o Line.o Group.o Material.o Pixmap.o Color.o Vector.o Utility.o 

PROJECT = objview

${PROJECT}:	${PROJECT}.o ${OFILES}
	${CC} ${LFLAGS} -o ${PROJECT} ${PROJECT}.o ${OFILES} ${LDFLAGS}

${PROJECT}.o: ${PROJECT}.${C} ${HFILES}
	${CC} ${CFLAGS} -c ${PROJECT}.${C}

objtest: objtest.o ${OFILES}
	${CC} ${LFLAGS} -o objtest objtest.o ${OFILES} ${LDFLAGS}

objtest.o: objtest.${C} ${HFILES}
	${CC} ${CFLAGS} -c objtest.${C}

File.o:  File.${C} File.${H}
	${CC} ${CFLAGS} -c File.${C}

OBJFile.o:  OBJFile.${C} File.${H} OBJFile.${H} MTLFile.${H} Vector.${H} Utility.${H}
	${CC} ${CFLAGS} -c OBJFile.${C}

MTLFile.o:  MTLFile.${C} File.${H} MTLFile.${H} ImageFile.${H} Color.${H} PolySurf.${H} Pixmap.${H}
	${CC} ${CFLAGS} -c MTLFile.${C}

ImageFile.o:  ImageFile.${C} File.${H} ImageFile.${H} Pixmap.${H} 
	${CC} ${CFLAGS} -c ImageFile.${C}

PolySurf.o:  PolySurf.${C} PolySurf.${H} Pixmap.${H} Vector.${H} Utility.${H}  MakeSpace.${H}
	${CC} ${CFLAGS} -c PolySurf.${C}

Face.o:  Face.${C} Face.${H} Color.${H} Pixmap.${H} Vector.${H} Utility.${H}
	${CC} ${CFLAGS} -c Face.${C}

Line.o:  Line.${C} Line.${H} Vector.${H} Utility.${H} MakeSpace.${H}
	${CC} ${CFLAGS} -c Line.${C}

Group.o:  Group.${C} Group.${H} MakeSpace.${H}
	${CC} ${CFLAGS} -c Group.${C}

Material.o:  Material.${C} Material.${H} Color.${H} Pixmap.${H} Vector.${H} Utility.${H}
	${CC} ${CFLAGS} -c Material.${C}

Pixmap.o:  Pixmap.${C} Pixmap.${H} 
	${CC} ${CFLAGS} -c Pixmap.${C}

Color.o:  Color.${C} Color.${H} 
	${CC} ${CFLAGS} -c Color.${C}
	
Vector.o:  Vector.${C} Vector.${H} Utility.${H} 
	${CC} ${CFLAGS} -c Vector.${C}

Utility.o:  Utility.${C} Utility.${H}
	${CC} ${CFLAGS} -c Utility.${C}

MakeSpace.o:  MakeSpace.${C} MakeSpace.${H}
	${CC} ${CFLAGS} -c MakeSpace.${C}

clean:
	rm -f *.o *~ core.* ${PROJECT}
