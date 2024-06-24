#ifndef __WINDOW__H__
#define __WINDOW__H__
#define WINDOW_HEIGHT 20
#define WINDOW_WIDTH 40
#define WINDOW_X 1
#define WINDOW_Y 1

WINDOW *create_window(int height, int width, int x, int y);
void game_over_window(WINDOW *play_window);
void game_manager(void);


#endif