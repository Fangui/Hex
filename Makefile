CC=gcc
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99 -g -o Hex
LDFLAGS=
LDLIBS=
 
SRC= Hex.c matrix.c

OBJ= ${SRC:.c=.o} 
all: Hex

Hex: ${OBJ} 
 
clean:
	rm -f ${OBJ}
	rm -f *.o
	rm Hex
