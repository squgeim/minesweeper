#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <ncurses.h>
#include "libminesweeper/minesweeper.h"

int window_init();
int window_exit();
int window_draw_game(MinesweeperCtx *game);

#endif
