/* mapping.h */
#ifndef MAPPING_H
#define MAPPING_H

#define MAP_ROWS 25
#define ROCK 35
#define LOCK_ROCK 36
#define USE_R 64
#define WA_L 178
#define HOLE 79
#define SPACE 32
#define SCORE_SUM_FOR_ROCK 40

void remove_char(int y, int x);
void clear_the_screen(int *current_size_y, int *current_size_x);
int copy_map(int map[][MAP_ROWS], int stash_map[][MAP_ROWS]);
void show_the_map(int map[][MAP_ROWS], int max_map_row, int max_map_col);
void game_over(void);
int move_the_object(int map[][MAP_ROWS],int *old_row, int *old_col, int delta_row, int delta_col);
int check_the_result(int map[][MAP_ROWS]);
void find_the_user(int map[][MAP_ROWS], int *user_map_y, int *user_map_x);
void add_score();
void show_the_top(void);
#endif
