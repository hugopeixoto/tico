NAME = tico
VERSION = 0.9

SRC = tico.c libutf/fputrune.c libutf/fgetrune.c libutf/rune.c
OBJ = ${SRC:.c=.o}

all: tico

tico: ${OBJ}
	@${CC} -o tico ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f ${NAME} ${OBJ}
