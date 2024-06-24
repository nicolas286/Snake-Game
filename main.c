#include <curses.h>
#include <stdlib.h>
#include "window.h"
#include "snake.h"

void game_manager(void);
void initialize_game(WINDOW *play_window, SnakeHead snake_head, Snake sn);


int main(void)
{
    game_manager();
    return 0;
}

void game_manager(void)
{
    WINDOW *play_window;
    Snake sn = new_snake();
    SnakeHead snake_head;

    initscr();
    noecho();
    curs_set(FALSE);
    cbreak();

    initialize_game(play_window, snake_head, sn);

    clear_snake(sn);
    endwin();

    return;
}


void initialize_game(WINDOW *play_window, SnakeHead snake_head, Snake sn)
{
    play_window = create_window(WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_X, WINDOW_Y);

    mvprintw(22, 2, "Press any key to start\n");
    mvprintw(23, 2, "Press ESC to exit game\n");

    snake_head = create_snakehead(SNAKE_Y, SNAKE_X, SNAKE_DIRECTION);

    sn = initialize_snake(sn, snake_head);
    draw_snake(play_window, snake_head, sn);
    
    
    keypad(stdscr, TRUE);
    
    getch();

    nodelay(stdscr, TRUE);
    create_food();
    move_snake(play_window, snake_head, sn);
}