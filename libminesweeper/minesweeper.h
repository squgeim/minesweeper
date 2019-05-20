#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

typedef struct {
  int rows;
  int cols;
  int bomb_count;
  int *bomb_positions;
  int *flag_positions;
} MinesweeperCtx;

MinesweeperCtx* msw_init(int rows, int cols);
int msw_quit();

#endif
