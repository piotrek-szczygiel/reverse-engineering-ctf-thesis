CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -fno-stack-protector

.PHONY: ${OUT} all decrypt test clean
.DEFAULT: all

all: decrypt generate

decrypt: decrypt.c
	${CC} ${CFLAGS} decrypt.c -o decrypt

generate: generate.c
	${CC} ${CFLAGS} generate.c -o generate

test: decrypt
	./decrypt

clean:
	${RM} decrypt generate
