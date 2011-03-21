CC = g++
C	= cpp
H	= h

CFLAGS = -g -Wall

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS = -framework Foundation -framework GLUT -framework OpenGL -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS = -lglut -lGL -lm
  endif
endif

HFILES  = 
OFILES  = 

PROJECT = viewer

${PROJECT}:	${PROJECT}.o $(OFILES)
	${CC} $(CFLAGS) -o ${PROJECT} ${PROJECT}.o $(OFILES) $(LDFLAGS)

${PROJECT}.o: ${PROJECT}.${C} $(HFILES)
	${CC} $(CFLAGS) -c ${PROJECT}.${C}

debug:
	make 'DFLAGS = /usr/lib/debug/malloc.o'

clean:
	rm -f core.* *.o *~ ${PROJECT} core.*

