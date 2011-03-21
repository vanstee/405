CC        = g++
C	  = cpp
CFLAGS    = -g

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -lglut -lGL -lm
  endif
endif

PROJECT   = shader

${PROJECT}: ${PROJECT}.o 
	${CC} ${CFLAGS} -o ${PROJECT} ${PROJECT}.o  ${LDFLAGS}

${PROJECT}.o:   ${PROJECT}.${C} 
	${CC} ${CFLAGS} -c ${PROJECT}.${C}

clean:
	rm -f core.* *.o *~ ${PROJECT}
