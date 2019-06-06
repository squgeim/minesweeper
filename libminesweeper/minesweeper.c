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

void init_bomb_counts(MinesweeperCtx *game, int *bomb_positions) {
  int i;
  MinesweeperCell *cell;

  for (i = 0; i < game->bomb_count; i++) {
    cell = game->cells[bomb_positions[i]];

    // Left
    if (cell->x > 0) {
      game
        ->cells[INDEX_FOR_CELL(game->rows, game->cols, cell->x - 1, cell->y)]
        ->bombs_count++;
    }

    // Right
    if (cell->x < game->cols) {
      game
        ->cells[INDEX_FOR_CELL(game->rows, game->cols, cell->x + 1, cell->y)]
        ->bombs_count++;
    }

    // Up
    if (cell->y > 0) {
      game
        ->cells[INDEX_FOR_CELL(game->rows, game->cols, cell->x, cell->y - 1)]
        ->bombs_count++;
    }

    // Down
    if (cell->y < game->rows) {
      game
        ->cells[INDEX_FOR_CELL(game->rows, game->cols, cell->x, cell->y + 1)]
        ->bombs_count++;
    }

    // Left Up
    if (cell->x > 0 && cell->y > 0) {
      game
        ->cells[INDEX_FOR_CELL(game->rows, game->cols, cell->x - 1, cell->y - 1)]
        ->bombs_count++;
    }

    // Right Up
    if (cell->x < game->cols && cell->y > 0) {
      game
        ->cells[INDEX_FOR_CELL(game->rows, game->cols, cell->x + 1, cell->y - 1)]
        ->bombs_count++;
    }

    // Left down
    if (cell->x < game->rows && cell->y > 0) {
      game
        ->cells[INDEX_FOR_CELL(game->rows, game->cols, cell->x - 1, cell->y + 1)]
        ->bombs_count++;
    }

    // Right down
    if (cell->x < game->rows && cell->y < game->cols) {
      game
        ->cells[INDEX_FOR_CELL(game->rows, game->cols, cell->x + 1, cell->y + 1)]
        ->bombs_count++;
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
      cell->bombs_count = 0;
      cell->is_revealed = false;
      cell->is_flagged = false;
      cell->x = j;
      cell->y = i;

      game->cells[k++] = cell;
    }
  }

  init_bomb_counts(game, bomb_positions);

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
