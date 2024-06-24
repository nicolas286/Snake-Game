#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include "window.h"
#include "snake.h"

int snake_length = 0;
Food fd;



SnakeHead create_snakehead(int position_y, int position_x, enum snake_direction direction)
{
    SnakeHead snake_head;
    snake_head.position_x = position_x;
    snake_head.position_y = position_y;
    snake_head.direction = direction;

    return snake_head;
}

Snake new_snake(void)
{
    return NULL;
}

Snake add_snake_element(Snake sn, int position_x, int position_y)
{
    SnakeElement *element;
    element = malloc(sizeof(*element));


    if(element == NULL)
        {
        fprintf(stderr, "Probleme allocation dynamique\n");
        exit(EXIT_FAILURE);
        }
    

    element->position_x = position_x;
    element->position_y = position_y;
    element->next = sn;

    return element;
}

Snake initialize_snake(Snake sn, SnakeHead snake_head)
{

    if(sn == NULL)
    {
        for(int i = 1; i <= SNAKE_STARTING_LENGTH; i++)
            {
            sn = add_snake_element(sn, snake_head.position_x - i, snake_head.position_y);
            snake_length++;
            }
    }

    return sn;

}


void draw_snake(WINDOW *play_window, SnakeHead snake_head, Snake sn)
{
    mvwaddch(play_window, snake_head.position_y, snake_head.position_x, ACS_BLOCK);

    while(sn != NULL)
    {
        mvwaddch(play_window, sn->position_y, sn->position_x, ACS_BLOCK);
        sn = sn->next;
    }

    refresh();
    wrefresh(play_window);
}

void move_snake(WINDOW *play_window, SnakeHead snake_head, Snake sn)
{
        Sleep(DELAY);
        wclear(play_window);

        Snake inverted_sn = new_snake();
        Snake new_sn = new_snake();

        inverted_sn = translate_snake(sn, snake_head);
        new_sn = invert_snake(inverted_sn);

        switch(snake_head.direction)
        {
            case UP:
            {
                snake_head.position_y -= 1;
                break;
            }
            case DOWN:
            {
                snake_head.position_y += 1;
                break;
            }
            case LEFT:
            {
                snake_head.position_x -= 1;
                break;
            }
            case RIGHT:
            {
                snake_head.position_x += 1;
                break;
            }
        }

        draw_snake(play_window, snake_head, new_sn);
        draw_food(play_window);
        box(play_window, 0, 0);

        refresh();
        wrefresh(play_window);
        clear_snake(sn);
        clear_snake(inverted_sn);

        snake_head = change_direction(snake_head);

        new_sn = eat_food(snake_head, new_sn, play_window);

        if(!game_over(snake_head, new_sn))
        {
            move_snake(play_window, snake_head, new_sn);
        }
        else 
        {
            game_over_window(play_window);
        }
}

Snake translate_snake(Snake sn, SnakeHead snake_head)
{
    Snake translated_sn = new_snake();
    int i = 1;

    while(i < snake_length)
    {
        translated_sn = add_snake_element(translated_sn, sn->next->position_x, sn->next->position_y);
        sn = sn->next;
        i++;
    }
    if(i == snake_length)
    {
        translated_sn = add_snake_element(translated_sn, snake_head.position_x, snake_head.position_y);
    }

    return translated_sn; // snake is returned translated but inverted

}

Snake invert_snake(Snake sn)
{
    Snake inverted_sn = new_snake();
    int i = 1;

    while(i <= snake_length)
        {
         inverted_sn = add_snake_element(inverted_sn, sn->position_x, sn->position_y);
         sn = sn->next;
         i++;
        }
    return inverted_sn;
}

SnakeHead change_direction(SnakeHead snake_head)
{
    int new_direction = getch();

            switch(new_direction)
            {
                case KEY_UP:
                {
                    if(snake_head.direction != DOWN) snake_head.direction = UP;
                    break;
                }

                case KEY_DOWN:
                {
                     if(snake_head.direction != UP) snake_head.direction = DOWN;
                    break;
                }

                case KEY_LEFT:
                {
                     if(snake_head.direction != RIGHT) snake_head.direction = LEFT;
                    break;
                }

                case KEY_RIGHT:
                {
                    if(snake_head.direction != LEFT) snake_head.direction = RIGHT;
                    break;
                }
            }
    
    return snake_head;
}

void create_food(void)
{
    srand(time(NULL));
    fd.position_x = (rand() % (WINDOW_WIDTH - 2)) + 1;
    fd.position_y = (rand() % (WINDOW_HEIGHT - 2)) + 1;
    return;
}

void draw_food(WINDOW *play_window)
{
    mvwaddch(play_window, fd.position_y, fd.position_x, ACS_DIAMOND);
    refresh();
    wrefresh(play_window);
}

Snake eat_food(SnakeHead snake_head, Snake sn, WINDOW *play_window)
{
    if(snake_head.position_x == fd.position_x && snake_head.position_y == fd.position_y)
    {
        sn = add_snake_element(sn, sn->position_x-1, sn->position_y-1);
        snake_length++;
        mvwdelch(play_window, fd.position_y, fd.position_x);
        create_food();
    }
    return sn;
}

bool game_over(SnakeHead snake_head, Snake sn)
{
    int i = 1;

    while(i <= snake_length)
    {
        if(snake_head.position_x == sn->position_x && snake_head.position_y == sn->position_y)
        {
            return true;
        }
        sn = sn->next;
        i++;
    }

    if(snake_head.position_x == 0 || snake_head.position_x == 39 || snake_head.position_y == 0 || snake_head.position_y == 19) return true;

    return false;
}

Snake clear_snake(Snake sn)
{
    Snake element;
    
    if(sn == NULL) return new_snake();

    element = sn->next;
    free(sn);

    return clear_snake(element);
}

