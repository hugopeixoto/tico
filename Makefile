SRC = tico.c libutf/fputrune.c libutf/fgetrune.c libutf/rune.c
OBJ = ${SRC:.c=.o}

all: tico

tico: ${OBJ}
	@${CC} -o tico ${OBJ} ${LDFLAGS}
