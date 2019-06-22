#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include <stdbool.h>

#define INDEX_FOR_CELL(rows, cols, x, y) (cols * y + x)
#define POSITION_X_FOR_INDEX(cols, index) (index % cols)
#define POSITION_Y_FOR_INDEX(cols, index) (index / cols)

#define BOMBS_RATIO (0.15) // 15% of all cells

typedef struct __MinesweeperCtx MinesweeperCtx;
typedef struct __MinesweeperCell MinesweeperCell;
typedef struct __MinesweeperCellList MinesweeperCellList;

struct __MinesweeperCell {
  int x;
  int y;
  int index;
  int bombs_count;
  bool is_bomb;
  bool is_revealed;
  bool is_flagged;
  MinesweeperCtx *game;
  MinesweeperCellList *list;
};

struct __MinesweeperCellList {
  MinesweeperCell *up;
  MinesweeperCell *left;
  MinesweeperCell *right;
  MinesweeperCell *down;
};

struct __MinesweeperCtx {
  int rows;
  int cols;
  int bomb_count;
  bool is_bombs_initialized;
  bool has_exploded;
  MinesweeperCell *first_cell;
  MinesweeperCell ***cells;
};

/**
 * GAME FUNCTIONS
 */
MinesweeperCtx* msw_init(int rows, int cols);
int msw_init_bomb_positions(MinesweeperCtx *game, MinesweeperCell *first_cell);
/**
 * GAME FUNCTIONS END
 */

/**
 * CELL FUNCTIONS
 */
int cell_reveal(MinesweeperCell *cell);
int cell_flag(MinesweeperCell *cell);
void get_surrounding_cells(
  MinesweeperCell *cell,
  MinesweeperCell **surrounding_cells
);
/**
 * CELL FUNCTIONS END
 */

int msw_quit();

#endif
