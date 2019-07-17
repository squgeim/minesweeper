#include <stdlib.h>
#include <ncurses.h>
#include <syslog.h>
#include <stdarg.h>

#include "utils/number.h"

#include "window.h"
#include "libminesweeper/minesweeper.h"

int window_disable_cursor(GameWindow *window);
int window_show_game_over(GameWindow *window);
int window_select_cell(GameWindow *window, int cell_x, int cell_y);

GameWindow *window_init(MinesweeperCtx *game) {
    GameWindow *win;
    WINDOW *local_win;
    int rows = game->rows,
        cols = game->cols;

    initscr();
    raw();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    refresh();

    local_win = newwin(
        rows * 2 + 1,
        cols * 2 + 1,
        (LINES - rows * 2 - 1) / 2,
        (COLS - cols * 2 - 1) / 2);

    wrefresh(local_win);

    win = (GameWindow *)malloc(sizeof(GameWindow));

    win->cursor_position_x = 0;
    win->cursor_position_y = 0;
    win->window = local_win;
    win->game = game;

    return win;
}

int window_exit(GameWindow *window)
{
    refresh();
    endwin();

    free(window);

    return 0;
}

int get_value_for_cell(MinesweeperCtx *game, int y, int x)
{
    MinesweeperCell *cell;

    if (!game->is_bombs_initialized)
        return ACS_CKBOARD;

    cell = game->cells[y][x];

    if (!cell->is_revealed && !game->has_exploded) {
        if (cell->is_flagged)
            return '#';

        return ACS_CKBOARD;
    }

    if (cell->is_bomb)
        return ACS_DIAMOND;

    if (cell->bombs_count > 0)
        return cell->bombs_count + 48; // Converting to ASCII

    return ' ';
}

int window_draw_game(GameWindow *window)
{
    MinesweeperCtx *game;
    int i, j, cell_i, cell_j;

    game = window->game;

    // Draw top row border:
    mvwaddch(window->window, 0, 0, ACS_ULCORNER);
    for (j = 1; j < game->cols * 2; j++)
        mvwaddch(window->window, 0, j, IS_EVEN(j) ? ACS_TTEE : ACS_HLINE);
    mvwaddch(window->window, 0, j, ACS_URCORNER);

    // Draw bottom row border:
    mvwaddch(window->window, game->rows * 2, 0, ACS_LLCORNER);
    for (j = 1; j < game->cols * 2; j++)
        mvwaddch(window->window, game->rows * 2, j, IS_EVEN(j) ? ACS_BTEE : ACS_HLINE);
    mvwaddch(window->window, game->rows * 2, j, ACS_LRCORNER);

    // Draw side borders:
    for (i = 1; i < game->rows * 2; i++) {
        mvwaddch(window->window, i, 0, IS_EVEN(i) ? ACS_LTEE : ACS_VLINE);
        mvwaddch(window->window, i, game->cols * 2, IS_EVEN(i) ? ACS_RTEE : ACS_VLINE);
    }

    // Draw cells and grid:
    for (i = 1, cell_i = 0; i < game->rows * 2; i++) {
        for (j = 1, cell_j = 0; j < game->cols * 2; j++) {
            if (IS_EVEN(i)) {
                mvwaddch(window->window, i, j, IS_EVEN(j) ? ACS_PLUS : ACS_HLINE);

                continue;
            }

            if (IS_EVEN(j)) {
                mvwaddch(window->window, i, j, ACS_VLINE);

                continue;
            }

            mvwaddch(window->window, i, j, get_value_for_cell(game, cell_i, cell_j++));
        }

        if (!IS_EVEN(i))
            cell_i++;
    }

    if (game->has_exploded) {
        window_disable_cursor(window);
        window_show_game_over(window);
    } else {
        window_select_cell(
            window,
            window->cursor_position_x,
            window->cursor_position_y);
    }

    wrefresh(window->window);
    return 0;
}

int window_select_cell(GameWindow *window, int cell_x, int cell_y)
{
    int cols = window->game->cols,
        rows = window->game->rows;
    // TODO: Check invalid cell

    if (cell_x > cols - 1) {
        cell_x = 0;
    } else if (cell_x < 0) {
        cell_x = cols - 1;
    }

    if (cell_y > rows - 1) {
        cell_y = 0;
    } else if (cell_y < 0) {
        cell_y = rows - 1;
    }

    int x = cell_x * 2 + 1;
    int y = cell_y * 2 + 1;

    window->cursor_position_x = cell_x;
    window->cursor_position_y = cell_y;

    wmove(window->window, y, x);

    return wrefresh(window->window);
}

int window_move_cursor(GameWindow *window, int ch)
{
    switch (ch) {
    case KEY_UP:
        return window_select_cell(
            window,
            window->cursor_position_x,
            window->cursor_position_y - 1);
    case KEY_DOWN:
        return window_select_cell(
            window,
            window->cursor_position_x,
            window->cursor_position_y + 1);
    case KEY_LEFT:
        return window_select_cell(
            window,
            window->cursor_position_x - 1,
            window->cursor_position_y);
    case KEY_RIGHT:
        return window_select_cell(
            window,
            window->cursor_position_x + 1,
            window->cursor_position_y);
    default:
        return -1;
    }
}

int window_reveal_current_cell(GameWindow *window)
{
    int x, y, cell_index;
    MinesweeperCtx *game;
    MinesweeperCell *cell;

    game = window->game;

    x = window->cursor_position_x;
    y = window->cursor_position_y;

    cell_index = INDEX_FOR_CELL(game->rows, game->cols, x, y);

    cell = game->cells[y][x];

    cell_reveal(cell);

    return window_draw_game(window);
}

int window_flag_current_cell(GameWindow *window)
{
    int x, y;
    MinesweeperCell *cell;

    x = window->cursor_position_x;
    y = window->cursor_position_y;

    cell = window->game->cells[y][x];

    cell_flag(cell);

    return window_draw_game(window);
}

int window_disable_cursor(GameWindow *window)
{
    curs_set(0);

    return 0;
}

int window_show_game_over(GameWindow *window)
{
    return 0;
}
