CC = clang
CFLAGS = -Wall -Wextra -g -std=c99 -O1

NASM = nasm
PYTHON = python3

.PHONY: ${OUT} all vm ctf test clean
.DEFAULT: all

all: ctf vm

ctf: ctf.nasm vm.inc
	@echo -n "Enter flag: "
	@${PYTHON} ctf.py > ctf.push
	${NASM} ctf.nasm -o ctf.rom
	xxd -i ctf.rom > ctf.h

vm: ctf vm.c
	${CC} ${CFLAGS} vm.c -o vm

test: ctf vm
	./vm ctf.rom

clean:
	${RM} ctf.rom ctf.h ctf.push vm
