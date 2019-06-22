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
  uint8_t i = 0;

  if (cell->list->up) {
    if (cell->list->up->list->left) {
      surrounding_cells[i++] = cell->list->up->list->left;
    }

    surrounding_cells[i++] = cell->list->up;

    if (cell->list->up->list->right) {
      surrounding_cells[i++] = cell->list->up->list->right;
    }
  }

  if (cell->list->left) {
    surrounding_cells[i++] = cell->list->left;
  }

  if (cell->list->right) {
    surrounding_cells[i++] = cell->list->right;
  }

  if (cell->list->down) {
    if (cell->list->down->list->left) {
      surrounding_cells[i++] = cell->list->down->list->left;
    }

    surrounding_cells[i++] = cell->list->down;

    if (cell->list->down->list->right) {
      surrounding_cells[i++] = cell->list->down->list->right;
    }
  }

  for (; i < 8; i++) {
    surrounding_cells[i] = 0;
  }
}

