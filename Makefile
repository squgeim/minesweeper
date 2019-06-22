CC=gcc
SRC=src

LFLAGS=-lncurses
DEBUG=-g
CFLAGS=-Wall
SOURCE=$(shell find $(SRC) -type f -name '*.c')

.PHONY: build clean

build: $(SOURCE)
	$(CC) -o bin/minesweeper $^ $(LFLAGS) $(CFLAGS)

%.c :
	$(CC) $(CFLAGS) $< -o bin/$@

clean:
	rm *.o
	rm **/*.o
