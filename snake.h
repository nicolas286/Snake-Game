#ifndef __SNAKE__H__
#define __SNAKE__H__
#define SNAKE_X 15
#define SNAKE_Y 10
#define SNAKE_DIRECTION UP
#define DELAY 100  
#define SNAKE_STARTING_LENGTH 4


enum snake_direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

typedef struct SnakeHead
{
    int position_x;
    int position_y; 
    enum snake_direction direction;
}SnakeHead;

typedef struct SnakeElement
{
    int position_x;
    int position_y;
    struct SnakeElement *next;
}SnakeElement, *Snake;

typedef struct Food
{
    int position_x;
    int position_y;
}Food;

SnakeHead create_snakehead(int position_x, int position_y, enum snake_direction direction);
void draw_snake(WINDOW *play_window, SnakeHead snake_head, Snake sn);
Snake new_snake(void);
Snake add_snake_element(Snake sn, int position_x, int position_y);
Snake initialize_snake(Snake sn, SnakeHead snake_head);
Snake translate_snake(Snake sn, SnakeHead snake_head);
Snake invert_snake(Snake sn);
Snake clear_snake(Snake sn);
SnakeHead change_direction(SnakeHead snake_head);
void create_food(void);
void draw_food(WINDOW *play_window);
Snake eat_food(SnakeHead snake_head, Snake sn, WINDOW *play_window);
void move_snake(WINDOW *play_window, SnakeHead snake_head, Snake sn);
bool game_over(SnakeHead snake_head, Snake sn);


#endif