#include <stdio.h>
#include <stdlib.h>

#include "minesweeper.h"

MinesweeperCtx* msw_init(int rows, int cols) {
  MinesweeperCtx *game = (MinesweeperCtx*) malloc(sizeof(MinesweeperCtx));

  if (!game) {
    fprintf(stderr, "There was an error trying to initialize Minesweeper. Maybe\
        you have run out of memory?");

    return NULL;
  }

  return game;
}

int msw_quit() {
  return 0;
}
