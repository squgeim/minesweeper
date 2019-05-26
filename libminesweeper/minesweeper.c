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

int init_cells(MinesweeperCtx *game, int *bomb_positions) {
  int i, j, k;
  MinesweeperCell *cell;

  for (i = 0, k = 0; i < game->rows; i++) {
    for (j = 0; j < game->cols; j++) {
      cell = (MinesweeperCell *) malloc(sizeof(MinesweeperCell));

      if (!cell) {
        return -1;
      }

      cell->is_bomb = (bool) array_has_value(
          bomb_positions,
          game->bomb_count,
          (i * game->cols) + j
        );
      cell->is_revealed = false;
      cell->is_flagged = false;
      cell->x = j;
      cell->y = i;

      game->cells[k++] = cell;
    }
  }

  return 0;
}

MinesweeperCtx* msw_init(int rows, int cols) {
  int total_cells, total_bombs;

  MinesweeperCtx *game = (MinesweeperCtx*) malloc(sizeof(MinesweeperCtx));

  total_cells = rows * cols;
  total_bombs = 15000 / total_cells; // 15% of the cells have a bomb

  int *bomb_positions = (int*) malloc(sizeof(int) * total_bombs);
  MinesweeperCell **cells =
    (MinesweeperCell**) malloc((sizeof(MinesweeperCell) * total_cells));

  if (!game || !bomb_positions || !cells) {
    fprintf(stderr, "There was an error trying to initialize Minesweeper. Maybe\
        you have run out of memory?");

    return NULL;
  }

  init_bomb_positions(bomb_positions, total_bombs, total_cells);

  game->rows = rows;
  game->cols = cols;
  game->bomb_count = total_bombs;
  game->cells = cells;

  init_cells(game, bomb_positions);

  return game;
}

int msw_quit(MinesweeperCtx *game) {
  free(game->cells);
  free(game);

  return 0;
}
