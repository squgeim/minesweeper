#include <stdlib.h>

#include "window.h"
#include "libminesweeper/minesweeper.h"

int process_character(char ch, MinesweeperCtx *game);

int main(int argc, char **argv)
{
  int i, j;
  int rows, cols;
  int cmd;
  MinesweeperCtx *game;

  window_init();

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

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      mvprintw(
        i,
        j,
        "%s",
        array_has_value(
          game->bomb_positions,
          game->bomb_count, i * rows + j
        )
          ? "+"
          : "-"
      );
    }
  }

  while((cmd = process_character(getch(), game)));

  window_exit();

  return 0;
}

int process_character(char ch, MinesweeperCtx *game) {
  if (ch == 'q') {
    if (msw_quit(game) == 0)
      return 0;
  }

  return 1;
}
