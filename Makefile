CC = clang
CFLAGS = -Wall -Wextra -g -std=c99

NASM = nasm

.PHONY: ${OUT} all vm ctf test clean
.DEFAULT: all

all: ctf vm

vm: vm.c
	${CC} ${CFLAGS} vm.c -o vm

ctf: ctf.nasm vm.inc
	${NASM} ctf.nasm -o ctf.rom

test: ctf vm
	./vm ctf.rom
