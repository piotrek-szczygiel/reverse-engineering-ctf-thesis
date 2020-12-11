CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3 -s -fno-stack-protector

.PHONY: ${OUT} all strcmp test clean
.DEFAULT: all

all: strcmp

strcmp: strcmp.c
	${CC} ${CFLAGS} strcmp.c -o strcmp

test: strcmp
	./strcmp

clean:
	${RM} strcmp
