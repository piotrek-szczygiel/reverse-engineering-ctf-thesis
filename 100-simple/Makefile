CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99 -O1

PYTHON = python

.PHONY: ${OUT} all simple ctf test clean
.DEFAULT: all

all: ctf simple

ctf:
	@echo -n "Enter flag: "
	@${PYTHON} -c 'import sys;f=open("flag.h","w");f.write("#define FLAG \"" + input() + "\"");f.close()'

simple: ctf simple.c
	${CC} ${CFLAGS} simple.c -o simple

test: ctf simple
	./simple

clean:
	${RM} flag.h simple
