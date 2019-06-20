CC=gcc
LFLAGS=-lncurses
CFLAGS=-g -Wall
OBJ = window.o libminesweeper/minesweeper.o libminesweeper/cell.o utils/array.o utils/number.o

build: $(OBJ)
	$(CC) -o bin/minesweeper main.c $^ $(LFLAGS) $(CFLAGS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm ./**/*.o
