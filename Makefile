CC=gcc
SRC=src
TEST=test

LFLAGS=-lncurses -ltinfo
DEBUG=-g
CFLAGS=-static -Wall -std=c99 -Isrc
SOURCE=$(shell find $(SRC) -type f -name '*.c')
OBJS=$(SOURCE:.c=.o)
TESTS=$(shell find . -type f \( -iname "*.c" ! -iname "main.c" \))
TESTS_OBJS=$(TESTS:.c=.o)

.PHONY: build debug clean

build: minesweeper
test: minesweeper_test

debug: CFLAGS += $(DEBUG)
debug: clean build clean

minesweeper: $(OBJS)
	$(CC) -o bin/minesweeper $^ $(CFLAGS) $(LFLAGS)

minesweeper_test: $(TESTS_OBJS)
	$(CC) -o bin/test $^ $(LFLAGS) $(CFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@find . -name '*.o' -delete
	@rm -f bin/minesweeper bin/test
