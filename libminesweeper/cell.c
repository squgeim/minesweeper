#include <stdint.h>
#include <stdbool.h>
#include <syslog.h>
#include <stdarg.h>

#include "minesweeper.h"


int explode(MinesweeperCtx *game, MinesweeperCell *cell) {
  game->has_exploded = true;

  return 0;
}

int cell_reveal(MinesweeperCtx *game, MinesweeperCell *cell) {
  MinesweeperCell *surrounding_cells[8];

  if (game->has_exploded) {
    return -1;
  }

  if (!game->is_bombs_initialized) {
    msw_init_bomb_positions(game, cell);
  }

  if (cell->is_bomb) {
    return explode(game, cell);
  }

  cell->is_revealed = true;

  if (cell->bombs_count == 0) {
    get_surrounding_cells(game, cell, surrounding_cells);

    for (uint8_t i = 0; i < 8; i++) {
      MinesweeperCell *surrounding_cell = surrounding_cells[i];

      if (!surrounding_cell) {
        continue;
      }

      if (surrounding_cell->is_revealed) {
        continue;
      }

      if (!surrounding_cell->is_bomb && surrounding_cell->bombs_count > 0) {
        surrounding_cell->is_revealed = true;

        continue;
      }

      cell_reveal(game, surrounding_cell);
    }
  }

  return 0;
}

int cell_flag(MinesweeperCtx *game, MinesweeperCell *cell) {
  cell->is_flagged = !cell->is_flagged;

  return 0;
}

void get_surrounding_cells(
  MinesweeperCtx *game,
  MinesweeperCell *cell,
  MinesweeperCell *surrounding_cells[8]
) {
  bool
    has_left_col = cell->x > 0,
    has_right_col = cell->x < (game->cols - 1),
    has_upper_row = cell->y > 0,
    has_lower_row = cell->y < (game->rows - 1);
  uint8_t i = 0;

  if (has_upper_row) {
    if (has_left_col) {
      surrounding_cells[i++] = game->cells[cell->y - 1][cell->x - 1];
    }

    surrounding_cells[i++] = game->cells[cell->y - 1][cell->x];

    if (has_right_col) {
      surrounding_cells[i++] = game->cells[cell->y - 1][cell->x + 1];
    }
  }

  if (has_left_col) {
    surrounding_cells[i++] = game->cells[cell->y][cell->x - 1];
  }

  if (has_right_col) {
    surrounding_cells[i++] = game->cells[cell->y][cell->x + 1];
  }

  if (has_lower_row) {
    if (has_left_col) {
      surrounding_cells[i++] = game->cells[cell->y + 1][cell->x - 1];
    }

    surrounding_cells[i++] = game->cells[cell->y + 1][cell->x];

    if (has_right_col) {
      surrounding_cells[i++] = game->cells[cell->y + 1][cell->x + 1];
    }
  }

  for (; i < 8; i++) {
    surrounding_cells[i] = 0;
  }
}

