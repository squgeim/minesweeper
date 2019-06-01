#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include <stdbool.h>

typedef struct {
  int x;
  int y;
  int bombs_count;
  bool is_bomb;
  bool is_revealed;
  bool is_flagged;
} MinesweeperCell;

typedef struct {
  int rows;
  int cols;
  int bomb_count;
  MinesweeperCell **cells;
} MinesweeperCtx;

MinesweeperCtx* msw_init(int rows, int cols);

/**
 * CELL FUNCTIONS
 */
int cell_reveal(MinesweeperCtx *game, MinesweeperCell *cell);
int cell_flag(MinesweeperCtx *game, MinesweeperCell *cell);
/**
 * CELL FUNCTIONS END
 */

int msw_quit();

#endif
