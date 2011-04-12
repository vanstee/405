CC        = g++
C	  = cpp
H	  = h

CFLAGS    = -g

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -lglut -lGL -lm
  endif
endif

HFILES = Model.${H} Vector.${H} Utility.${H}
OFILES = Model.o Vector.o Utility.o

PROJECT   = mipmaps

${PROJECT}: ${PROJECT}.o ${OFILES}
	${CC} ${CFLAGS} -o ${PROJECT} ${PROJECT}.o ${OFILES} ${LDFLAGS} -lm

${PROJECT}.o:   ${PROJECT}.${C} ${HFILES} ${INCFLAGS}
	${CC} ${CFLAGS} -c ${INCFLAGS} ${PROJECT}.${C}
	
Model: Model.o 
	${CC} ${CFLAGS} -o Model Model.o  ${LDFLAGS} -lm

Model.o:   Model.${C} Model.${H}
	${CC} ${CFLAGS} -c ${INCFLAGS} Model.${C}
	
Vector.o: Vector.${C} Vector.${H} Utility.${H} 
	${CC} $(CFLAGS) -c Vector.${C}

Utility.o: Utility.${C} Utility.${H}
	${CC} $(CFLAGS) -c Utility.${C}

clean:
	rm -f ${project} *.o *~ core.*
