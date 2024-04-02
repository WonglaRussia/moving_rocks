/* menu_map_editor.c */
#include <ncurses.h> 	//getch(),printw(),move() e.t.c.
#include <stdlib.h>		//malloc();
#include "file.h"		//load_map();
#include "mapping.h"	//WA_L

//here we show the instructions
static void show_side_bar(int row, int col) {
	move(row,col);
	printw("Keys");
	move(row+1,col);
	printw("w - wall");
	move(row+2,col);
	printw("space - remove an object");
	move(row+3,col);
	printw("s - save");
	return;
}
//show the border of the showed map (do not confuse with the walls)
static void show_borders(int row, int col) {
	int y, x, y_min, x_min, y_max, x_max, ch;
	y_min = row - 1;
	x_min = col - 1;
	y_max = y_min + MAP_ROWS + 2;
	x_max = x_min + MAP_ROWS + 2;
	for(y = y_min; y < y_max; y++){
	  for(x = x_min; x < x_max; x++){
			 if(y == y_min && x == x_min) ch = 201;			//top-left corner
		else if(y == y_min && x == x_max) ch = 187;			//top-right corner
		else if(y == y_max && x == x_min) ch = 200;			//bottom-left corner
		else if(y == y_max && x == x_max) ch = 188;			//bottom-right corner
		else if(y == y_min || y == y_max) ch = 205;
		else if(x == x_min || x == x_max) ch = 186;
	  move(y,x);
	  addch(ch);
	  }
	}
	return;
}
//show the map itself + show the cursor
static void show_the_map_edition(int map[][MAP_ROWS], int row, int col, int cur_y, int cur_x) {
	int x, y;
	char ch;
	for(y = 0 ; y < MAP_ROWS; ++y){
	  for(x = 0 ; x < MAP_ROWS; ++x){
		move(row + y, col + x);
		ch = map[y][x];				//using int as argument here is not correct
		addch(ch);
	  }
	}
	move(row + cur_y, col + cur_x); 				//show where is the cursor
	addch('@');
	move(row + MAP_ROWS + 1, col);
	printw("x = %d/ty = %d", cur_x + 1, cur_y + 1);	//print the map coord
	return;
}
//show the side bar + map + borders + cursor
static void show_the_editor(int map[][MAP_ROWS],int max_row, int max_col, int cur_y, int cur_x) {
	show_side_bar((max_row / 10) * 2, (max_col/2) - 12);
	show_borders(4,4);
	show_the_map_edition(map,4,4,cur_y,cur_x);
	return;
}

//before save we will can save the minimal check if the player cant win
static int check_if_the_map_is_ready(int map[][MAP_ROWS]) {
	return 0;
}
//just full the map with spases
static void clear_the_map(int map[][MAP_ROWS]){
	int x, y;
	for(y = 0 ; y < MAP_ROWS; y++){
	  for(x = 0 ; x < MAP_ROWS; x++){
		map[y][x] = ' ';
	  }
	}
	return;
}

//editor itsef
int edit()
{
	int map[MAP_ROWS][MAP_ROWS];
	int max_row, max_col;
	int act;
	unsigned int y, x;					//current coord under editing
	y = x = 0;
	getmaxyx(stdscr, max_row, max_col);
	clear_the_map(map);
	clear();
	show_the_editor(map, max_row, max_col, y, x);
	
	do{
	  act = getch();
	  switch(act){
	  case(KEY_UP): 	{y--; break;}
	  case(KEY_DOWN):	{y++; break;}
	  case(KEY_RIGHT):	{x++; break;}
	  case(KEY_LEFT):	{x--; break;}
	  case(' '): 		{map[y][x] = SPACE; break;}
	  case('w'): 		{map[y][x] = WA_L; break;}
	  case('r'): 		{map[y][x] = ROCK; break;}
	  case('h'): 		{map[y][x] = HOLE; break;}
	  case(KEY_RESIZE): {
		getmaxyx(stdscr, max_row, max_col);
		break;
	  }
	  case('c'):	{
	    clear_the_map(map);
		break;
	  }
	  case('s'):{
		//here check the map and append to the file
	    break;
	  }
	  default: break;
	  }
	  x %= MAP_ROWS;	//limite coord position by map size
	  y %= MAP_ROWS;
	  clear();
	  show_the_editor(map, max_row, max_col, y, x);
	  check_if_the_map_is_ready(map);
	}
	while(1);
	return 0;
}
	
