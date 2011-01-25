CC		= g++
C		= cpp

CFLAGS		= -g `Magick++-config --cppflags`
LFLAGS		= -g `Magick++-config --ldflags`

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -lMagick++ -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -L /usr/lib64/ -lglut -lGL -lMagick++ -lm
  endif
endif

PROJECT		= glmagick

${PROJECT}:	${PROJECT}.o
	${CC} ${LFLAGS} -o ${PROJECT} ${PROJECT}.o ${LDFLAGS}

${PROJECT}.o:	${PROJECT}.${C}
	${CC} ${CFLAGS} -c ${PROJECT}.${C}

clean:
	rm -f core.* *.o *~ ${PROJECT}
