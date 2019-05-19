#include "window.h"
#include "libminesweeper/minesweeper.h"

int process_character(char ch, MinesweeperCtx *game);

int main()
{
  int cmd;
  MinesweeperCtx *game;

  window_init();

  game = msw_init(16, 16);

  if (!game) {
    fprintf(stderr, "Could not initialize game.");

    return -1;
  }

  while((cmd = process_character(getch(), game)));

  window_exit();

  return 0;
}

int process_character(char ch, MinesweeperCtx *game) {
  if (ch == 'q') {
    if (msw_quit() == 0)
      return 0;
  }

  return 1;
}
