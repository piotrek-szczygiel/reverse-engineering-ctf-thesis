CC = clang
CFLAGS = -Wall -Wextra -g -std=c99

NASM = nasm

.PHONY: ${OUT} all vm ctf test clean
.DEFAULT: all

all: ctf vm

ctf: ctf.nasm vm.inc
	${NASM} ctf.nasm -o ctf.rom
	xxd -i ctf.rom > ctf.h

vm: ctf vm.c
	${CC} ${CFLAGS} vm.c -o vm

test: ctf vm
	./vm ctf.rom

clean:
	${RM} ctf.rom vm
