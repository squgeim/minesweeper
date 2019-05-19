#ifndef MINESWEEPER_H
#define MINESWEEPER_H

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
