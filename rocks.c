/* rocks.c */
#include <ncurses.h>
#include "mapping.h"
#include "maps.h"


int *score;

void add_score(int addition)
{
	*score += addition;
	return;
}

int main() {
//int *score;
//*score = 40;
initscr();
keypad(stdscr, 1);
curs_set(0);
int row, col, act, user_map_y, user_map_x;

row = col = 0;				

find_the_user(map, &user_map_y, &user_map_x); //define the user coordinates
show_the_map( map, (sizeof(map) / sizeof(map[0])), (sizeof(map[0]) /sizeof(map[0][0])) );  
do {  
  int current_size_y; int current_size_x; 		// for fuction clearing screen while changing size

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
  
  clear_the_screen( &current_size_y, &current_size_x );
  //show_the_top();
  show_the_map( map, (sizeof(map) / sizeof(map[0])), (sizeof(map[0]) /sizeof(map[0][0])) );
  refresh();
  //if (check_the_result(map) == 200)			//if no free rocks you won
  {											// REWRITE go to the next map
    ;
  }
 } 
while(act != 'q');

endwin();
return 0;
}

