#include <stdlib.h>
#include <ncurses.h>

#include "utils/array.h"

#include "window.h"
#include "libminesweeper/minesweeper.h"

int process_character(char ch, MinesweeperCtx *game);

int main(int argc, char **argv) {
  int rows, cols;
  int cmd;
  MinesweeperCtx *game;
  WINDOW *window;

  if (argc != 3) {
    rows = cols = 16;
  } else {
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
  }

  game = msw_init(rows, cols);

  if (!game) {
    fprintf(stderr, "Could not initialize game.");

    return -1;
  }

  window = window_init(rows, cols);
  /*window_draw_game(game);*/

  while((cmd = process_character(getch(), game)));

  window_exit();

  return 0;
}

int process_character(char ch, MinesweeperCtx *game) {
  if (ch == 'q') {
    if (msw_quit(game) == 0)
      return 0;
  }

  /*switch (ch) {*/
    /*case KEY_LEFT:*/
    /*case KEY_RIGHT:*/
    /*case KEY_UP:*/
    /*case KEY_DOWN:*/
      /*[>window_move_cursor(game, ch);<]*/
  /*}*/

  return 1;
}
