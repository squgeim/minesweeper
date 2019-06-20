#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <stdarg.h>

#include "../utils/array.h"

#include "minesweeper.h"

int random_number(int max) {
  return rand() % max;
}

void init_bomb_positions(
  int *bomb_positions,
  int total_bombs,
  int total_cells,
  int *ignore_cells,
  int ignore_cells_count
) {
  int i, tmp;
  srand(time(NULL));

  i = 0;
  while(1) {
    tmp = random_number(total_cells);
    if (
      !array_has_value(bomb_positions, total_bombs, tmp) &&
      !array_has_value(ignore_cells, ignore_cells_count, tmp)
    ) {
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
    cell = game
      ->cells
          [POSITION_Y_FOR_INDEX(game->cols, bomb_positions[i])]
          [POSITION_X_FOR_INDEX(game->cols, bomb_positions[i])];

    cell->is_bomb = true;

    // Left
    if (cell->x > 0) {
      game->cells[cell->y][cell->x - 1]->bombs_count++;
    }

    // Right
    if (cell->x < (game->cols - 1)) {
      game->cells[cell->y][cell->x + 1]->bombs_count++;
    }

    // Up
    if (cell->y > 0) {
      game->cells[cell->y - 1][cell->x]->bombs_count++;
    }

    // Down
    if (cell->y < (game->rows - 1)) {
      game->cells[cell->y + 1][cell->x]->bombs_count++;
    }

    // Left Up
    if (cell->x > 0 && cell->y > 0) {
      game->cells[cell->y - 1][cell->x - 1]->bombs_count++;
    }

    // Right Up
    if (cell->x < (game->cols - 1) && cell->y > 0) {
      game->cells[cell->y - 1][cell->x + 1]->bombs_count++;
    }

    // Left down
    if (cell->x > 0 && cell->y < (game->rows - 1)) {
      game->cells[cell->y + 1][cell->x - 1]->bombs_count++;
    }

    // Right down
    if (cell->x < (game->cols - 1) && cell->y < (game->rows - 1)) {
      game->cells[cell->y + 1][cell->x + 1]->bombs_count++;
    }
  }
}

int init_cells(MinesweeperCtx *game) {
  int i, j, k, index;
  MinesweeperCell *cell, **cell_row;

  for (i = 0, k = 0; i < game->rows; i++) {
    cell_row =
      (MinesweeperCell **) malloc(sizeof(MinesweeperCell*) * game->cols);
    game->cells[i] = cell_row;

    for (j = 0; j < game->cols; j++) {
      cell = (MinesweeperCell *) malloc(sizeof(MinesweeperCell));

      if (!cell) {
        return -1;
      }

      index = (i * game->cols) + j;

      cell->is_bomb = false;
      cell->bombs_count = 0;
      cell->is_revealed = false;
      cell->is_flagged = false;
      cell->x = j;
      cell->y = i;
      cell->index = index;

      game->cells[i][j] = cell;
    }
  }

  return 0;
}

MinesweeperCtx* msw_init(int rows, int cols) {
  int total_cells, total_bombs;
  MinesweeperCell ***cells;

  syslog(LOG_INFO, "Initializing game with size: %dx%d", cols, rows);

  MinesweeperCtx *game = (MinesweeperCtx*) malloc(sizeof(MinesweeperCtx));

  total_cells = rows * cols;
  total_bombs = (int) (0.2 * total_cells); // 20% of the cells have a bomb

  syslog(LOG_INFO, "Total bombs: %d", total_bombs);

  cells = (MinesweeperCell***) malloc((sizeof(MinesweeperCell **) * rows));

  if (!game || !cells) {
    fprintf(stderr, "There was an error trying to initialize Minesweeper. Maybe\
 you have run out of memory?");

    return NULL;
  }

  game->rows = rows;
  game->cols = cols;
  game->bomb_count = total_bombs;
  game->is_bombs_initialized = false;
  game->cells = cells;

  init_cells(game);

  return game;
}

int msw_init_bomb_positions(MinesweeperCtx *game, MinesweeperCell *first_cell) {
  int *bomb_positions, total_cells, clear_cells[9], j;
  MinesweeperCell *surrounding_cells[8];

  bomb_positions = (int*) malloc(sizeof(int) * game->bomb_count);
  total_cells = game->rows * game->cols;

  if (!bomb_positions) {
    syslog(LOG_ERR, "Could not initialize game due to insufficient memory.");

    return -1;
  }

  get_surrounding_cells(game, first_cell, surrounding_cells);
  for (j = 0; j < 8; j++) {
    clear_cells[j] = surrounding_cells[j]
      ? surrounding_cells[j]->index
      : -1;
  }
  clear_cells[j] = first_cell->index;

  init_bomb_positions(
    bomb_positions,
    game->bomb_count,
    total_cells,
    clear_cells,
    9
  );

  init_bomb_counts(game, bomb_positions);

  game->is_bombs_initialized = true;

  return 0;
}

int msw_quit(MinesweeperCtx *game) {
  free(game->cells);
  free(game);

  return 0;
}
