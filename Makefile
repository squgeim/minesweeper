CC=gcc
CFLAGS=-lncurses

minesweeper: window.o libminesweeper.o array.o
	$(CC) -o bin/minesweeper main.c minesweeper.o array.o $< $(CFLAGS)

window.o:
	$(CC) -c window.c $< $(CFLAGS)

libminesweeper.o: array.o
	$(CC) -c libminesweeper/minesweeper.c

array.o:
	$(CC) -c utils/array.c
