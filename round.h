/* round.h */
#ifndef ROCKS_H
#define ROCKS_H

extern int score;
extern int map[MAP_ROWS][MAP_ROWS];

void add_score(int addition);
int play_the_map(int current_map[][MAP_ROWS]);

#endif