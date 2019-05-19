#ifndef _WINDOW_H
#define _WINDOW_H

#include <ncurses.h>

int window_init();
int window_exit();
int window_printStr(char *str);

#endif
