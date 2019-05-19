#include "window.h"

int window_init() {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  return 0;
}

int window_exit() {
  refresh();
  endwin();

  return 0;
}
