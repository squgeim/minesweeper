CC=gcc
CFLAGS=-lncurses

minesweeper: window.o libminesweeper.o
	$(CC) -o bin/minesweeper main.c minesweeper.o $< $(CFLAGS)

window.o:
	$(CC) -c window.c $< $(CFLAGS)

libminesweeper.o:
	$(CC) -c libminesweeper/minesweeper.c
