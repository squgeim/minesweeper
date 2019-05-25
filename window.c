#include <stdlib.h>
#include <ncurses.h>

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
      rows * 2 + 1,
      cols *2 + 1,
      (LINES - rows * 2 - 1) / 2,
      (COLS - cols * 2 - 1) / 2
    );

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

int is_even(int num) {
  return num % 2 == 0;
}

int window_draw_game(GameWindow *window, MinesweeperCtx *game) {
  int i, j, cell_i, cell_j;

  // Draw top row border:
  mvwaddch(window->window, 0, 0, ACS_ULCORNER);
  for (j = 1; j < game->cols * 2; j++) {
    mvwaddch(window->window, 0, j, is_even(j) ? ACS_TTEE : ACS_HLINE);
  }
  mvwaddch(window->window, 0, j, ACS_URCORNER);

  // Draw bottom row border:
  mvwaddch(window->window, game->rows * 2, 0, ACS_LLCORNER);
  for (j = 1; j < game->cols * 2; j++) {
    mvwaddch(window->window, game->rows * 2, j, is_even(j) ? ACS_BTEE : ACS_HLINE);
  }
  mvwaddch(window->window, game->rows * 2, j, ACS_LRCORNER);

  // Draw side borders:
  for (i = 1; i < game->rows * 2; i++) {
    mvwaddch(window->window, i, 0, is_even(i) ? ACS_LTEE: ACS_VLINE);
    mvwaddch(window->window, i, game->cols * 2, is_even(i) ? ACS_RTEE: ACS_VLINE);
  }

  // Draw cells and grid:
  for (i = 1, cell_i = 0; i < game->rows * 2; i++) {
    for (j = 1, cell_j = 0; j < game->cols * 2; j++) {
      if (!is_even(i)) {
        mvwaddch(window->window, i, j, is_even(j) ? (cell_j++, ACS_VLINE) : ACS_CKBOARD);
      } else {
        mvwaddch(window->window, i, j, is_even(j) ? ACS_PLUS : ACS_HLINE);
      }
    }
    cell_i++;
  }

  wrefresh(window->window);
  refresh();
  return 0;
}
