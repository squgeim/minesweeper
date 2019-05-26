#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <ncurses.h>
#include "libminesweeper/minesweeper.h"

typedef struct {
  WINDOW* window;
  int cursor_position_x;
  int cursor_position_y;
} GameWindow;

GameWindow* window_init(int rows, int cols);
int window_exit();

int window_draw_game(GameWindow *window, MinesweeperCtx *game);
int window_move_cursor(GameWindow *window, MinesweeperCtx *game, int direction);
int window_reveal_current_cell(GameWindow *window, MinesweeperCtx *game);
int window_flag_current_cell(GameWindow *window, MinesweeperCtx *game);

#endif
