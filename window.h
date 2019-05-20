#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <ncurses.h>

int window_init();
int window_exit();
int window_printStr(char *str);

#endif
