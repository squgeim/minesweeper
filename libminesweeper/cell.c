#include <stdbool.h>

#include "minesweeper.h"

void check_all_directions(MinesweeperCtx *game, MinesweeperCell *cell);

int cell_reveal(
  MinesweeperCtx *game,
  MinesweeperCell *cell,
  bool is_automatic
) {
  if (!is_automatic && cell->is_bomb) {
    // explod()
    return 0;
  }

  if (cell->bombs_count == 0) {
    /*check_all_directions(game, cell);*/
  }

  cell->is_revealed = true;

  return 0;
}

int cell_flag(MinesweeperCtx *game, MinesweeperCell *cell) {
  cell->is_flagged = !cell->is_flagged;

  return 0;
}
