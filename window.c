#include "window.h"
#include "libminesweeper/minesweeper.h"

int window_init() {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  return 0;
}

int window_exit() {
  refresh();
  endwin();

  return 0;
}

int window_draw_game(MinesweeperCtx *game) {
  int i, j;

  for (i = 0; i < game->rows; i++) {
    for (j = 0; j < game->cols; j++) {
      printw("_");
    }
    printw("\n");
  }

  return 0;
}
