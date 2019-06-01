#include "minesweeper.h"

int cell_reveal(MinesweeperCtx *game, MinesweeperCell *cell) {
  cell->is_revealed = true;

  return 0;
}

int cell_flag(MinesweeperCtx *game, MinesweeperCell *cell) {
  cell->is_flagged = !cell->is_flagged;

  return 0;
}
