#include <stdlib.h>
#include <ncurses.h>

#include "utils/number.h"

#include "window.h"
#include "libminesweeper/minesweeper.h"

int window_select_cell(GameWindow *window, MinesweeperCtx *game, int cell_x, int cell_y);

GameWindow* window_init(int rows, int cols) {
  GameWindow *win;
  WINDOW *local_win;

  initscr();
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

int get_value_for_cell(MinesweeperCtx *game, int y, int x) {
  MinesweeperCell *cell;

  cell = game->cells[y * game->rows + x];

  if (!cell->is_revealed) {
    if (cell->is_flagged) {
      return '#';
    }

    return ACS_CKBOARD;
  }

  if (cell->is_bomb) {
    return ACS_DIAMOND;
  }

  if (cell->bombs_count > 0) {
    return cell->bombs_count;
  }

  return ' ';
}

int window_draw_game(GameWindow *window, MinesweeperCtx *game) {
  int i, j, cell_i, cell_j;

  // Draw top row border:
  mvwaddch(window->window, 0, 0, ACS_ULCORNER);
  for (j = 1; j < game->cols * 2; j++) {
    mvwaddch(window->window, 0, j, IS_EVEN(j) ? ACS_TTEE : ACS_HLINE);
  }
  mvwaddch(window->window, 0, j, ACS_URCORNER);

  // Draw bottom row border:
  mvwaddch(window->window, game->rows * 2, 0, ACS_LLCORNER);
  for (j = 1; j < game->cols * 2; j++) {
    mvwaddch(window->window, game->rows * 2, j, IS_EVEN(j) ? ACS_BTEE : ACS_HLINE);
  }
  mvwaddch(window->window, game->rows * 2, j, ACS_LRCORNER);

  // Draw side borders:
  for (i = 1; i < game->rows * 2; i++) {
    mvwaddch(window->window, i, 0, IS_EVEN(i) ? ACS_LTEE: ACS_VLINE);
    mvwaddch(window->window, i, game->cols * 2, IS_EVEN(i) ? ACS_RTEE: ACS_VLINE);
  }

  // Draw cells and grid:
  for (i = 1, cell_i = 0; i < game->rows * 2; i++) {
    for (j = 1, cell_j = 0; j < game->cols * 2; j++) {
      if (IS_EVEN(i)) {
        mvwaddch(window->window, i, j, IS_EVEN(j) ? ACS_PLUS : ACS_HLINE);

        continue;
      }

      if (IS_EVEN(j)) {
        mvwaddch(window->window, i, j, ACS_VLINE);

        continue;
      }

      mvwaddch(window->window, i, j, get_value_for_cell(game, cell_i, cell_j++));
    }
    cell_i++;
  }

  window_select_cell(window, game, window->cursor_position_x, window->cursor_position_y);

  wrefresh(window->window);
  return 0;
}

int window_select_cell(GameWindow *window, MinesweeperCtx *game, int cell_x, int cell_y) {
  // TODO: Check invalid cell

  if (cell_x > game->cols - 1) {
    cell_x = 0;
  } else if (cell_x < 0) {
    cell_x = game->cols - 1;
  }

  if (cell_y > game->rows - 1) {
    cell_y = 0;
  } else if (cell_y < 0) {
    cell_y = game->rows - 1;
  }

  int x = cell_x * 2 + 1;
  int y = cell_y * 2 + 1;

  window->cursor_position_x = cell_x;
  window->cursor_position_y = cell_y;

  wmove(window->window, y, x);

  return wrefresh(window->window);
}

int window_move_cursor(GameWindow *window, MinesweeperCtx *game, int ch) {
  switch (ch) {
    case KEY_UP:
      return window_select_cell(
          window,
          game,
          window->cursor_position_x,
          window->cursor_position_y - 1
        );
    case KEY_DOWN:
      return window_select_cell(
          window,
          game,
          window->cursor_position_x,
          window->cursor_position_y + 1
        );
    case KEY_LEFT:
      return window_select_cell(
          window,
          game,
          window->cursor_position_x - 1,
          window->cursor_position_y
        );
    case KEY_RIGHT:
      return window_select_cell(
          window,
          game,
          window->cursor_position_x + 1,
          window->cursor_position_y
        );
    default:
      return -1;
  }
}

int window_reveal_current_cell(GameWindow *window, MinesweeperCtx *game) {
  int x, y;

  x = window->cursor_position_x;
  y = window->cursor_position_y;

  game->cells[y * game->cols + x]->is_revealed = true;

  return window_draw_game(window, game);
}

int window_flag_current_cell(GameWindow *window, MinesweeperCtx *game) {
  int x, y;

  x = window->cursor_position_x;
  y = window->cursor_position_y;

  game->cells[y * game->cols + x]->is_flagged = true;

  return window_draw_game(window, game);
}
