CC = gcc
CFLAGS = -Wall -Wextra -std=c99

.PHONY: ${OUT} all decrypt test clean
.DEFAULT: all

all: decrypt

decrypt: decrypt.c
	${CC} ${CFLAGS} decrypt.c -o decrypt

test: decrypt
	./decrypt

clean:
	${RM} decrypt
