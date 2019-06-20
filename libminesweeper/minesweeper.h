#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include <stdbool.h>

#define INDEX_FOR_CELL(rows, cols, x, y) (cols * y + x)
#define POSITION_X_FOR_INDEX(cols, index) (index % cols)
#define POSITION_Y_FOR_INDEX(cols, index) (index / cols)

#define BOMBS_RATIO (0.15) // 15% of all cells

typedef struct {
  int x;
  int y;
  int index;
  int bombs_count;
  bool is_bomb;
  bool is_revealed;
  bool is_flagged;
} MinesweeperCell;

typedef struct {
  int rows;
  int cols;
  int bomb_count;
  bool is_bombs_initialized;
  bool has_exploded;
  MinesweeperCell ***cells;
} MinesweeperCtx;

MinesweeperCtx* msw_init(int rows, int cols);
int msw_init_bomb_positions(MinesweeperCtx *game, MinesweeperCell *first_cell);

/**
 * CELL FUNCTIONS
 */
int cell_reveal(MinesweeperCtx *game, MinesweeperCell *cell);
int cell_flag(MinesweeperCtx *game, MinesweeperCell *cell);
void get_surrounding_cells(
  MinesweeperCtx *game,
  MinesweeperCell *cell,
  MinesweeperCell **surrounding_cells
);
/**
 * CELL FUNCTIONS END
 */

int msw_quit();

#endif
