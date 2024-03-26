/* rocks.c */
#include <ncurses.h>
#include "mapping.h"	//show_the_top find_the_user
#include "maps.h"		//extern int current_map[MAP_ROWS][MAP_ROWS];


int score;

void add_score(int addition)
{
	extern int score;
	score += addition;
	return;
}

int play_the_map(int current_map[][MAP_ROWS])
{	
	int act, user_map_y, user_map_x;				//"user_map" - coord of the user
	int map[MAP_ROWS][MAP_ROWS];					//temporal map for playing
	 
	copy_map(map, current_map);						//now do not use (change) the current map
	find_the_user(map, &user_map_y, &user_map_x); 	//define the user coordinates
	show_the_top();
	show_the_map( map, (sizeof(map) / sizeof(map[0])), (sizeof(map[0]) /sizeof(map[0][0])) );
	do {
	  act = getch(); 								//action
	  switch(act){
	  case(KEY_UP):{
		if (move_the_object(map, &user_map_y, &user_map_x, - 1, 0) == 200)
			return 200;
		break;
	  }
	  case(KEY_DOWN):{
		if (move_the_object(map, &user_map_y, &user_map_x, +1, 0) == 200)
			return 200;
		break;
	  }
	  case(KEY_LEFT):{
		if (move_the_object(map, &user_map_y, &user_map_x, 0, - 1) == 200)
			return 200;
		break;
	  }
	  case(KEY_RIGHT):{
		if (move_the_object(map, &user_map_y, &user_map_x, 0, +1) == 200)
			return 200;
		break;
	  }
	  case(KEY_RESIZE):{
		clear();								//to exclude multiplication of the garbage
		break;
	  }
	  default: 
	  /* clear();
		printw("BW is %d", work_bw);
		getch();  //to check output by int */
	  break;
	  }	  
	  show_the_top();
	  show_the_map( map, (sizeof(map) / sizeof(map[0])), (sizeof(map[0]) /sizeof(map[0][0])) );
	  refresh();	  
	  if (check_the_result(map) == 100)			//if there is no free rocks you win
	  {											//REWRITE go to the next map
		endwin();
		return 0;
	  }
	 } 
	while(act != 'q');
return 0;
}
