CC		= g++
C		= cpp
H		= h

CFLAGS		= -g

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -lglut -lGL -lm
  endif
endif

PROJECT		= pixmaps

${PROJECT}:	${PROJECT}.o ${OBJS}
	${CC} ${CFLAGS} -o ${PROJECT} ${PROJECT}.o ${OBJS} ${LDFLAGS}

${PROJECT}.o:	${PROJECT}.${C}
	${CC} ${CFLAGS} -c ${PROJECT}.${C}
