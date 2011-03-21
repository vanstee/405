#----------------------------------------------
#    Makefile for compiling a program that uses
#    the Matrix and Vector classes
#----------------------------------------------
#
#  Programmer: Donald House
#  Date: March 8, 1999
#
#  Copyright (C) - Donald H. House. 2005
#

CC      = g++
C	= cpp
H	= h

CFLAGS 	= -g -Wall

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -lglut -lGL -lm
  endif
endif

HFILES 	= Matrix.${H} Vector.${H} Utility.${H}
OFILES 	= Matrix.o Vector.o Utility.o

PROJECT = hello

${PROJECT}:	${PROJECT}.o $(OFILES)
	${CC} $(CFLAGS) -o ${PROJECT} ${PROJECT}.o $(OFILES) $(LDFLAGS)

${PROJECT}.o: ${PROJECT}.${C} $(HFILES)
	${CC} $(CFLAGS) -c ${PROJECT}.${C}

Matrix.o: Matrix.${C} Matrix.${H} Vector.${H} Utility.${H} 
	${CC} $(CFLAGS) -c Matrix.${C}

Vector.o: Vector.${C} Vector.${H} Utility.${H} 
	${CC} $(CFLAGS) -c Vector.${C}

Utility.o: Utility.${C} Utility.${H}
	${CC} $(CFLAGS) -c Utility.${C}

debug:
	make 'DFLAGS = /usr/lib/debug/malloc.o'

clean:
	rm -f core.* *.o *~ ${PROJECT} core.*

