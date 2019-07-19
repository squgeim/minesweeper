#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <ncurses.h>
#include "libminesweeper/minesweeper.h"

typedef struct {
    WINDOW *window;
    MinesweeperCtx *game;
    int cursor_position_x;
    int cursor_position_y;
} GameWindow;

int window_init(GameWindow *window, MinesweeperCtx *game);
int window_exit(GameWindow *window);

int window_draw_game(GameWindow *window);
int window_move_cursor(GameWindow *window, int direction);
int window_reveal_current_cell(GameWindow *window);
int window_flag_current_cell(GameWindow *window);

#endif
