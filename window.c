#include <stdlib.h>

#include "window.h"
#include "libminesweeper/minesweeper.h"

GameWindow* window_init(int rows, int cols) {
  GameWindow *win;
  WINDOW *local_win;

  initscr();
  curs_set(0);
  raw();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  refresh();

  local_win = newwin(
      rows * 2,
      cols * 2,
      (LINES - rows * 2 - 2) / 2,
      (COLS - cols * 2 - 2) / 2
    );
  box(local_win, 0, 0);

  wrefresh(local_win);

  win = (GameWindow*) malloc(sizeof(GameWindow));

  win->cursor_position_x = 0;
  win->cursor_position_y = 0;
  win->window = local_win;

  return win;
}

int window_exit() {
  refresh();
  endwin();

  return 0;
}

int window_draw_game(GameWindow *window, MinesweeperCtx *game) {
  return 0;
}
