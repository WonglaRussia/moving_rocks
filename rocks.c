/* rocks.c */
#include <ncurses.h>
#include "mapping.h"	//show_the_top find_the_user
#include "maps.h"		//extern int map[MAP_ROWS][MAP_ROWS];

int score;
void add_score(int addition)
{
	extern int score;
	score += addition;
	return;
}

int main() {
score = 40;

initscr();
keypad(stdscr, 1); 							//esc seq for moving by arrows
curs_set(0);
int  act, user_map_y, user_map_x;
find_the_user(map, &user_map_y, &user_map_x); 	//define the user coordinates
show_the_top();									//tepeating sequence of two function REWRITE?
show_the_map( map, (sizeof(map) / sizeof(map[0])), (sizeof(map[0]) /sizeof(map[0][0])) );  
do {  

  act = getch(); 
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
  case(KEY_RESIZE):{				//
	clear();
	break;
  }
  default: 
/*   clear();
	printw("Pressed key is %d", act);
	getch();  //to check output by int */
  break;
  }
  
  show_the_top();
  show_the_map( map, (sizeof(map) / sizeof(map[0])), (sizeof(map[0]) /sizeof(map[0][0])) );
  refresh();
  if (check_the_result(map) == 200)			//if no free rocks you won
  {											// REWRITE go to the next map
	endwin();;
  }
 } 
while(act != 'q');

endwin();
return 0;
}

