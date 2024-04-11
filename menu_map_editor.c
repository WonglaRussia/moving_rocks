/* menu_map_editor.c */
#include <ncurses.h> 	//getch(),printw(),move() e.t.c.
#include <stdlib.h>		//malloc();
#include <string.h>		//strlen();strcpy();
#include <stdarg.h>		//va_list va_start va_arg
#include "file.h"		//load_map();
#include "mapping.h"	//WA_L SPACE ROCK HOLE e.t.c

/* REWRITE
 * Add load map. 
 * Add saving to the certain round position (not append only)*/

//Jist show the list of messages. q = how many strings.
static void shw_msg(int q, ...){
	char *tmp;
	int row, col;
	getmaxyx(stdscr, row, col);
	row = (row / 2) - (q / 2); //first line
	
	va_list arguments;
	va_start(arguments, q);
	
	clear();
	for(int i = 0; i < q; i++, row++) {
	  tmp = va_arg(arguments, char*);
	  move(row, col / 2 - (strlen(tmp) / 2));
	  printw("%s",tmp);
	}
return;	
}
//here we show the instructions
static void show_side_bar(int row, int col) {
	move(row,col);
	printw("Keys");
	move(row+1,col);
	printw("Space - Remove an object.");
	move(row+2,col);
	printw("w - Put wall.");
	move(row+3,col);
	printw("r - Put a rock.");
	move(row+4,col);
	printw("h - Put a hole.");
	move(row+5,col);
	printw("s - Append the map to the campaing file.");
	move(row+6,col);
	printw("c - Clear current map.");
	move(row+7,col);
	printw("Keep cursor where user starts when you saves the map.");
	move(row+8,col);
	printw("n - Rename the compaign name.");
	move(row+9,col);
	printw("q - Main menu.");
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
static void show_map(int map[][MAP_ROWS], int row, int col, unsigned int cur_y, unsigned int cur_x, char *campaign_name) {
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
	//print the map coord
	mvprintw(row + MAP_ROWS + 1, col, "                        ");
	mvprintw(row + MAP_ROWS + 1, col,"x = %d y = %d", (cur_x + 1), (cur_y + 1));	
	mvprintw(row + MAP_ROWS + 2, col,"%s",campaign_name);
	return;
}
//show the side bar + map + borders + cursor
static void show_editor(int map[][MAP_ROWS],int max_row, int max_col, int cur_y, int cur_x, char *campaign_name) {
	clear();
	show_side_bar((max_row/10)*3, (max_col/10)*3+MAP_ROWS+6);
	show_borders((max_row/10)*3, (max_col/10)*3);
	show_map(map, (max_row/10)*3, (max_col/10)*3, cur_y, cur_x, campaign_name);
	return;
}
// 1 = map is not ready (minimal check of the map)
static int check_map(int map[][MAP_ROWS]) {
	int x, y;
	int r, h;
	r = h = 0;
    for(y = 0 ; y < MAP_ROWS; ++y)
	  for(x = 0 ; x < MAP_ROWS; ++x)
		if(map[y][x] == ROCK) r++;
		else if(map[y][x] == HOLE) h++;
	if(h < 1)
	  return 1;
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
//To change the campaign (file) name.
static void ask_file_name(char *file_name) {
	char *question = "Would you like to type new campaign name? (y)es";
	char *notification = "Type the campaign name";
	char answer;
	int max_row, max_col;
	getmaxyx(stdscr, max_row, max_col);
	shw_msg(2,question,file_name);
	answer = getch();
	if(answer == 'Y' || answer == 'y' || answer == '\n') {
	  shw_msg(1,notification);
	  move((max_row/2) + 1, (max_col/2)-(strlen(notification)/2) );
	  getstr(file_name);
	}
	return;
}
//campaign_name - name of the file, y, x - user position.
static void save(int map[MAP_ROWS][MAP_ROWS], char *campaign_name, int y, int x) {
	char *file_extention = ".rrmap";
	if(check_map(map) == 0) {
//Change the name?
	  ask_file_name(campaign_name);  
//Fill full file_name
	  char *file_campaign = malloc(strlen(campaign_name) + strlen(file_extention) + 1);
	  strcpy(file_campaign, campaign_name);
	  strcat(file_campaign, file_extention);
//Put the user on the map
	  map[y][x] = '@';
//Try to save the map.
	  if (append_map_to_the_file(map, file_campaign) == -1) {  
		shw_msg(1,"Something went wrong while opening the file!");
		getch();
	  } else {
		shw_msg(1,"Saved!");
		getch();
	  }
	  free(file_campaign);
	  map[y][x] = SPACE;
	}
	else {
	  shw_msg(1,"The map is not playable!");
	  getch();
	}
	return;
}
//editor itsef
int edit()
{
	char campaign_name[21];
	int map[MAP_ROWS][MAP_ROWS];
	int max_row, max_col;
	int act;
	unsigned int y, x;					//current coord under editing
	//default
	strcpy(campaign_name, "user_campaign"); 
	clear_the_map(map);
	y = x = 0;  						//cursor position
	clear();
	getmaxyx(stdscr, max_row, max_col);
	show_editor(map, max_row, max_col, y, x, campaign_name);	
	
	do{
	  curs_set(0);
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
	  case('c'):		{clear_the_map(map); break; }
	  case('n'):{
		ask_file_name(campaign_name);
		show_editor(map, max_row, max_col, y, x,campaign_name);
		break;
		}
	  case('s'):{
		save(map,campaign_name,y,x); 
		show_editor(map, max_row, max_col, y, x,campaign_name);
		break;
		}
	  case(KEY_RESIZE):{
		getmaxyx(stdscr, max_row, max_col); 
		show_editor(map, max_row, max_col, y, x,campaign_name);
		break;
		}
	  default: break;
	  }
	  x %= MAP_ROWS;	//to limit coordinates by map size
	  y %= MAP_ROWS;
	  show_map(map, (max_row/10)*3, (max_col/10)*3, y, x, campaign_name);
	  
	  refresh();
	  
	}
	while(act != 'q');
	return 0;
}