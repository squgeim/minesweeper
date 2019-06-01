CC=gcc
LFLAGS=-lncurses
CFLAGS=
OBJ = window.o libminesweeper/minesweeper.o libminesweeper/cell.o utils/array.o

build: $(OBJ)
	$(CC) -o bin/minesweeper main.c $^ $(LFLAGS) $(CFLAGS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
