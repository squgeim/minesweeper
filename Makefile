CC=gcc
SRC=src

LFLAGS=-lncurses
DEBUG=-g
CFLAGS=-Wall -std=c99
SOURCE=$(shell find $(SRC) -type f -name '*.c')
OBJS=$(SOURCE:.c=.o)

.PHONY: build debug clean

build: minesweeper

debug: CFLAGS += $(DEBUG)
debug: clean build clean

minesweeper: $(OBJS)
	$(CC) -o bin/minesweeper $^ $(LFLAGS) $(CFLAGS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -r src/*.o
