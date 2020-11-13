CC = gcc
CFLAGS = -Wall -Wextra -Wno-deprecated-declarations -std=c99 -m32 -fno-stack-protector -no-pie

.PHONY: ${OUT} all greeter test clean
.DEFAULT: all

all: greeter

greeter: greeter.c
	${CC} ${CFLAGS} greeter.c -o greeter

test: greeter
	./greeter

clean:
	${RM} greeter