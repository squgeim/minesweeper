#include <stdlib.h>
#include <ncurses.h>
#include <syslog.h>
#include <stdarg.h>

#include "utils/array.h"

#include "window.h"
#include "libminesweeper/minesweeper.h"

int process_character(int ch, GameWindow *window, MinesweeperCtx *game);

int main(int argc, char **argv) {
  int rows, cols;
  MinesweeperCtx *game;
  GameWindow *window;

  openlog("minesweeper", (LOG_CONS | LOG_PERROR | LOG_PID), LOG_USER);

  if (argc != 3) {
    // TODO: take all the space available
    rows = 16;
    cols = 32;
  } else {
    // TODO: Limit by available screen space
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
  }

  syslog(LOG_INFO, "Initializing game with size: %dx%d", cols, rows);

  game = msw_init(rows, cols);

  if (!game) {
    syslog(LOG_ERR, "Could not initialize game, most probably due to lack of \
memory.");
    fprintf(stderr, "Could not initialize game.");

    return -1;
  }

  window = window_init(rows, cols);
  window_draw_game(window, game);

  while(process_character(getch(), window, game));

  syslog(LOG_INFO, "Exiting because the user asked to.");

  window_exit();

  closelog();

  return 0;
}

int process_character(int ch, GameWindow *window, MinesweeperCtx *game) {
  if (ch == 'q') {
    if (msw_quit(game) == 0)
      return 0;
  }

  switch (ch) {
    case KEY_LEFT:
    case KEY_RIGHT:
    case KEY_UP:
    case KEY_DOWN:
      window_move_cursor(window, game, ch);

      break;
    case 10: // Enter key
      window_reveal_current_cell(window, game);

      break;
    case ' ':
      window_flag_current_cell(window, game);

      break;
  }

  return 1;
}
