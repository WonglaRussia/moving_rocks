/* mapping.c */
#include <ncurses.h>
#include "mapping.h"
#include "maps.h"
void remove_char(int y, int x){
  move(y, x);
  addch(' ');
  refresh();
  return;
}

void show_the_map(int map[][MAP_ROWS], int max_map_row, int max_map_col){
	int x, y, ch, start_row, start_col;
	getmaxyx(stdscr, start_row, start_col);
	start_row = start_row / 2 - max_map_row / 2;    //right-upper corner
	start_col = start_col / 2 - max_map_col / 2;
	for(y = 0 ; y < max_map_row; y++){
	  for(x = 0 ; x < max_map_col; x++){
		move(start_row + y, start_col + x);			//corner coordinates + current map coordinates
		ch = map[y][x];
		addch(ch);		
	  }
	};
	move(0,0);
	return;
}

void game_over(void) {
	clear();
	printw("GAME OVER");
	getch();
	return;
}

int move_the_object(int map[][MAP_ROWS],int *old_row, int *old_col, int delta_row, int delta_col)
{
  int figure, destination, new_row, new_col;		//look what do we try to move (figure) and where (destination)
  
  new_row = *old_row + delta_row;					//destination coordinates
  new_col = *old_col + delta_col;
  
  figure = map[*old_row][*old_col];					//what to move
  destination = map[new_row][new_col];				//where to move
  
  if((figure == destination)|| (destination == LOCK_ROCK) ||(destination == WA_L)) 		//if moves to destination or moves the rock to the rock
    return 100;										//do not move any object exit									
  if(destination == ROCK) {
	if (move_the_object(map, &new_row, &new_col, delta_row, delta_col) == 100) //try to move the next rock (destination coordinates)
	  return 100;									//the very next rock is immovable
  }												//do not move any object exit
  if(destination == HOLE){
	if(figure == USER)
		game_over();
	else if (figure == ROCK)
		figure = LOCK_ROCK;
  }
  
  map[new_row][new_col] = figure;					//place the figure to the destination
  map[*old_row][*old_col] = SPACE;					//place the SPACE to the previous place
  
  if(figure == USER) {								//relocate the user in globap program
   *old_row = new_row;								//REWRITE
   *old_col = new_col;
  }
  return 0;
}

int check_the_result(int map[][MAP_ROWS]) 
{
  int y,x;

  for(y = 0; y < MAP_ROWS; y++) 
    for(x = 0; x < (sizeof(map[0]) / sizeof(map[0][0])); x++)
      if(map[y][x] == HOLE)			//IF any HOLE stil is on the map pass by
  	  return 0;
  clear();
  printw("YOU WIN!");				//theri is no any hole
  getch();							//REWRITE
  return 0;
}
