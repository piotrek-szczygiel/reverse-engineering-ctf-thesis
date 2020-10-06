CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99 -O1 -lraylib

PYTHON = python

.PHONY: ${OUT} all game test clean
.DEFAULT: game

game: game.c
	${CC} ${CFLAGS} game.c -o game

test: game
	./game

clean:
	${RM} game
