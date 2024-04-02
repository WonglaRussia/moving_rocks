/* mapping.c */

//Few functions working with the map the screen and objects on it.

#include <ncurses.h>
#include "mapping.h"
#include "maps.h"		// extern int map[MAP_ROWS][MAP_ROWS];
#include "round.h" 		// void add_score(int addition)

#define SCORE_SUM_FOR_ROCK 40

int remove_the_user(int map[][MAP_ROWS], int usr_y, int usr_x) {
	map[usr_y][usr_x] = SPACE;
	return 0;	
}

void game_over(void) {
	clear();
	int row, col;
	getmaxyx(stdscr, row, col);
	move(row / 2, (col - 8)/2);
	printw("GAME OVER");
	getch();
	return;
}

//Copy to the "map" from "current map" (to make reading map files).
//REWRITE map in files!
int copy_map(int map[][MAP_ROWS], int const stash_map[][MAP_ROWS])
{
	int y, x;
	for(y = 0; y < MAP_ROWS; y++){
		for(x=0; x < MAP_ROWS; x++){
			map[y][x] = stash_map[y][x];
		}
	}
	return 0;
}

void show_the_map(int map[][MAP_ROWS], int max_map_row, int max_map_col, int *usr_y, int *usr_x)
{
	int x, y, ch, start_row, start_col;
	getmaxyx(stdscr, start_row, start_col);			//REWRITE? examine size when KEY_RESIZE?
	start_row = start_row / 2 - max_map_row / 2;    //right-upper corner
	start_col = start_col / 2 - max_map_col / 2;
	for(y = 0 ; y < max_map_row; y++){
	  for(x = 0 ; x < max_map_col; x++){
		move(start_row + y, start_col + x);			//corner coordinates + current map coordinates
		ch = map[y][x];
		addch(ch);
	  }
	move(start_row + *usr_y, start_col + *usr_x);	//show the user
	addch('@');
	};
	move(0,0);
	return;
}
//rename to play_the_move? (REWRITE)
int move_the_object(int map[][MAP_ROWS],int *old_row, int *old_col, int delta_row, int delta_col)
{
  int figure, destination, new_row, new_col;	//look what do we try to move (figure) and where (destination)
  
  new_row = *old_row + delta_row;				//destination coordinates
  new_col = *old_col + delta_col;
  
  figure = map[*old_row][*old_col];				//stuff try to move
  destination = map[new_row][new_col];			//stuff placed in the destination
  
//Immovable situations. to wall, OR rock to rock
  if(\
  (destination == WA_L) || \
  ((figure == LOCK_ROCK || figure == ROCK) && (destination == ROCK || destination == LOCK_ROCK))\
  ) return 100; else							//100 means do not move any object								
//try to move the very next rock in the same direction
  if(destination == ROCK || destination == LOCK_ROCK) {	  
	if (move_the_object(map, &new_row, &new_col, delta_row, delta_col) == 100)
	  return 100;								//next rock is immovable
  }												
/*From here onward only all immoveble situation are excluded.
  Hence we move: user , rock , locked rock.*/
  switch(figure){
  case(ROCK):{
    if(destination == SPACE){
	  map[*old_row][*old_col] = SPACE;		//move rock
	  map[new_row][new_col] = ROCK;
	  return 0;
    } else
    if(destination == HOLE){
	  map[*old_row][*old_col] = SPACE;		//move rock as locked
	  map[new_row][new_col] = LOCK_ROCK;
	  add_score(SCORE_SUM_FOR_ROCK);		//add score
	  return 0;
    }
  }
  case(LOCK_ROCK):{
	if(destination == SPACE){
	  map[*old_row][*old_col] = HOLE;		
	  map[new_row][new_col] = ROCK;
	  add_score(-1 * SCORE_SUM_FOR_ROCK);	//take the score back
	  return 0;
    } else
	if(destination == HOLE){
	  map[*old_row][*old_col] = HOLE;		
	  map[new_row][new_col] = LOCK_ROCK;
	  return 0;
	}
  }
  case(HOLE):;			//it means user is hense here
  case(SPACE):{ 		
  	*old_row = new_row;	//relocate the user without changing the map
	*old_col = new_col;
	return 0;
  }
  }

  printw("PLAYGROUND ERROR in function move_the_object");
  return 0;
}

int check_the_result(int map[][MAP_ROWS])  //REWRITE add checking uneven number of rocks and holes
{
  int y,x;
  int h,r;
  h = r = 0;
  for(y = 0; y < MAP_ROWS; y++) 
    for(x = 0; x < (sizeof(map[0]) / sizeof(map[0][0])); x++)
      if(map[y][x] == HOLE) h++;
	  else if(map[y][x] == ROCK) r++;
  if(r == 0 || h == 0)
	return 100;
  return 0;
}

void find_the_user(int map[][MAP_ROWS], int *user__y, int *user__x) //returns the user location
{
  int y,x;
  for(y = 0; y < MAP_ROWS; y++) 
    for(x = 0; x < (sizeof(map[0]) / sizeof(map[0][0])); x++)
      if(map[y][x] == USE_R){						//fond the user
		*user__y = y;
		*user__x = x;
	  };
	  return;
  clear();
  printw("CANT FIND THE USER! MAP is incorrect");	//theri is no any user on the map
  getch();											//REWRITE
  return;
}
						//shows fringed the header with score
void show_the_top(void)
{

	int max_x, y, x;
	max_x = getmaxx(stdscr);
	
	for(y = 0 ; y < 3; y++){
	  for(x = 0 ; x < max_x; x++){
	    if ( y == 0 || y == 2 || x == 0 || (x == (max_x - 1)) )
		{
		  move(y, x);
		  addch('#');
		}
	  }
	}
    move(1, (max_x / 2) - 5);
	printw("SCORE:%d", score);
	return;
}
