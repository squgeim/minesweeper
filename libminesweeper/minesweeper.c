#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/array.h"

#include "minesweeper.h"

int random_number(int max) {
  return rand() % max;
}

void init_bomb_positions(int *bomb_positions, int total_bombs, int total_cells) {
  int i, tmp;
  srand(time(NULL));

  i = 0;
  while(1) {
    tmp = random_number(total_cells);
    if (!array_has_value(bomb_positions, total_bombs, tmp)) {
      bomb_positions[i] = tmp;
      i++;
    }

    if (i == total_bombs) {
      break;
    }
  }
}

MinesweeperCtx* msw_init(int rows, int cols) {
  int total_cells, total_bombs;

  MinesweeperCtx *game = (MinesweeperCtx*) malloc(sizeof(MinesweeperCtx));

  total_cells = rows * cols;
  total_bombs = 15000 / total_cells; // 15% of the cells have a bomb

  int *bomb_positions = (int*) malloc(sizeof(int) * total_bombs);
  int *flag_positions = (int*) malloc(sizeof(int) * total_cells);

  if (!game || !bomb_positions || !flag_positions) {
    fprintf(stderr, "There was an error trying to initialize Minesweeper. Maybe\
        you have run out of memory?");

    return NULL;
  }

  init_bomb_positions(bomb_positions, total_bombs, total_cells);

  game->rows = rows;
  game->cols = cols;
  game->bomb_count = total_bombs;
  game->bomb_positions = bomb_positions;
  game->flag_positions = flag_positions;

  return game;
}

int msw_quit(MinesweeperCtx *game) {
  free(game->bomb_positions);
  free(game->flag_positions);
  free(game);

  return 0;
}
