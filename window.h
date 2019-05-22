#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <ncurses.h>
#include "libminesweeper/minesweeper.h"

WINDOW* window_init(int rows, int cols);
int window_exit();
int window_draw_game(MinesweeperCtx *game);
int window_move_cursor(MinesweeperCtx *game, char direction);

#endif
