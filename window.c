#include "window.h"
#include "libminesweeper/minesweeper.h"

WINDOW* window_init(int rows, int cols) {
  WINDOW *local_win;

  initscr();
  raw();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  refresh();

  local_win = newwin(rows, cols, (LINES - rows - 2) / 2, (COLS - cols - 2) / 2);
  box(local_win, 0, 0);

  wrefresh(local_win);

  return local_win;
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
      printw("%c", 35);
    }
    printw("\n");
  }

  return 0;
}
