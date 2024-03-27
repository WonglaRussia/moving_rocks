/* menu.c */
#include <ncurses.h>
#include <string.h>

enum position { Continue,Start,Load,Save,Map_Editor,Play_on_line };

static void draw_menu (int current_position) {
	static char *option[6];
	option[0] = "Continue";
	option[1] = "Start";
	option[2] = "Load";
	option[3] = "Save";
	option[4] = "Map_Editor";
	option[5] = "Play_on-line";
	
	int x, y, max_row, max_col;
	int corner_y, corner_x;				//right-upper corner
	int high = 3 * 6;					//only 3 rows for each 6 options (REWRITE?)
	int width = 14;						//Length of "Play_on-line" + 4
	int i;
	
	getmaxyx(stdscr, max_row, max_col);
	corner_y = (max_row / 2) - (high / 2);		//here y,x is the left upper corner of the menu
	corner_x = (max_col / 2) - (width / 2);
	
	clear();
	for(i = 0; i < 6 ; i++ ) {
	  y = corner_y + i;
	  x = corner_x; 						//position of the option
	  move(y, (max_col / 2) - (strlen(option[i])/2) );
	  printw("%s", option[i]);
	  if(i == current_position) {
		move(y, x);
		addch('*');
	  }
	}	
	refresh();
}

int menu() {
	//REWRITE? (potentionaly it can be global)
	enum position cur_position;
	int input;
	cur_position = Continue;
	for(;;){
	  if(cur_position < 0)
		cur_position = 5;
	  else if(cur_position > 5)
		cur_position %= 6;
	  
	  draw_menu(cur_position);
	  
	  input = getch();
	  switch(input){
	  case(KEY_UP):		{ --cur_position; break; }
	  case(KEY_DOWN):	{ ++cur_position; break; }
	  case('\n'):		return cur_position;
	  default: ;
	  }
	}
}