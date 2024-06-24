#include <curses.h>
#include "window.h"
#include "snake.h"

WINDOW *create_window(int height, int width, int x, int y)
{
    WINDOW *new_window;
    new_window = newwin(height, width, x, y);
    box(new_window, 0, 0);
    mvwprintw(new_window, 0, 1, "Snake game");

    refresh();
    wrefresh(new_window);
    
    return new_window;
}

void game_over_window(WINDOW *play_window)
{
    wclear(play_window);
    box(play_window, 0, 0);
    mvwprintw(play_window, 10, 10, "Game Over");
    refresh();
    wrefresh(play_window);
    nodelay(stdscr, FALSE);
    getch();
    game_manager();
}