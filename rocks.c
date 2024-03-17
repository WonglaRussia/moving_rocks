/* rocks.c */
#include <ncurses.h>
#include "mapping.h"
#include "maps.h"

int main() {

initscr();
keypad(stdscr, 1);
curs_set(0);
int row, col, act, user_map_y, user_map_x;

row = col = 0;				
//user_map_y = 6;						//REWRITE TAKE POSITITION from the file with maps
//user_map_x = 6;
find_the_user(map, &user_map_y, &user_map_x);
//map[user_map_y][user_map_x] = USE_R;
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
  clear();
  show_the_map( map, (sizeof(map) / sizeof(map[0])), (sizeof(map[0]) /sizeof(map[0][0])) );
  refresh();
  check_the_result(map);			//if no free rocks you won
 } 
while(act != 'q');
endwin();
return 0;
}