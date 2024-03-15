/* blocks.c */
#include <ncurses.h>
#include "mapping.h"

int map[10][MAP_ROWS] = {
	{WA_L  ,  WA_L ,  WA_L , WA_L  ,  WA_L ,  WA_L ,  WA_L ,  WA_L ,  WA_L ,  WA_L},  
	{WA_L  ,  SPACE,  HOLE ,  SPACE,  WA_L ,  SPACE,  SPACE,  SPACE,  SPACE,  WA_L},  
	{WA_L  ,  SPACE,  SPACE,  SPACE,  WA_L ,  ROCK ,  SPACE,  SPACE,  SPACE,  WA_L},  
	{WA_L  ,  SPACE,  SPACE,  SPACE,  WA_L ,  SPACE,  SPACE,  SPACE,  SPACE,  WA_L},  	
	{WA_L  ,  SPACE,  SPACE,  SPACE,  WA_L ,  SPACE,  SPACE,  SPACE,  SPACE,  WA_L},  
	{WA_L  ,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  HOLE ,  WA_L},  
	{WA_L  ,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  WA_L},  
	{WA_L  ,  SPACE,  SPACE,  SPACE,  SPACE,  ROCK ,  SPACE,  SPACE,  SPACE,  WA_L},  
	{WA_L  ,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  WA_L},  
	{WA_L  ,  WA_L ,  WA_L , WA_L  ,  WA_L ,  WA_L ,  WA_L ,  WA_L ,  WA_L ,  WA_L}
};

int main() {

initscr();
keypad(stdscr, 1);
curs_set(0);
int row, col, act, user_map_y, user_map_x;

row = col = 0;
user_map_y = 6;
user_map_x = 6;
map[user_map_y][user_map_x] = USER;
show_the_map( map, (sizeof(map) / sizeof(map[0])), (sizeof(map[0]) /sizeof(map[0][0])) );  
do {  
  act = getch(); 
  remove_char(row, col);  
  switch(act){
  case(KEY_UP):{
	move_the_object(map, &user_map_y, &user_map_x, - 1, 0);
	break;
  }
  case(KEY_DOWN):{
	move_the_object(map, &user_map_y, &user_map_x, +1, 0);
	break;
  }
  case(KEY_LEFT):{
	move_the_object(map, &user_map_y, &user_map_x, 0, - 1);
	break;
  }
  case(KEY_RIGHT):{
	move_the_object(map, &user_map_y, &user_map_x, 0, +1);
	break;
  }
  default: break;
  }
  
  show_the_map( map, (sizeof(map) / sizeof(map[0])), (sizeof(map[0]) /sizeof(map[0][0])) );
  refresh();
  check_the_result(map);
 } 
while(act != 'q');
endwin();
return 0;
}