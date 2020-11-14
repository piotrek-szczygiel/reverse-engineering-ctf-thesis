CC = gcc
CFLAGS = -Wall -Wextra -Wno-deprecated-declarations -std=c99 -m32 -fno-stack-protector -no-pie -fno-pic

.PHONY: ${OUT} all secret-shell test clean
.DEFAULT: all

all: secret-shell

secret-shell: secret-shell.c
	${CC} ${CFLAGS} secret-shell.c -o secret-shell

test: secret-shell
	./secret-shell

clean:
	${RM} secret-shell