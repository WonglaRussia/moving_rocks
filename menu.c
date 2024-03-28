/* menu.c */
#include <ncurses.h>
#include <string.h>

enum position \
{ \
Continue, \
Start, \
Load_Charachter, \
Save, \
Map_Editor, \
Play_on_line, \
Exit
};

static void draw_menu(int current_position) {
	static char *option[7];
	option[0] = "Continue";
	option[1] = "Start";
	option[2] = "Load_Charachter";
	option[3] = "Save";
	option[4] = "Map_Editor";
	option[5] = "Play_on-line";
	option[6] = "Exit";
	
	int y, max_row, max_col;
	int corner_y;						//start of the option line
	int high = 3 * 7;					//only 3 rows for each 6 options (REWRITE?)
	int i;

	getmaxyx(stdscr, max_row, max_col);
	corner_y = (max_row / 2) - (high / 2);		//here y,x is the left upper corner of the menu
	
	clear();
	for(i = 0; i < 7 ; i++ ) {
	  y = corner_y + i; 				//a current position of the option
	  move(y, (max_col / 2) - (strlen(option[i])/2) );
	  printw("%s", option[i]);
	  if(i == current_position) {
		move(y, (max_col/2) - strlen(option[i])/2 - 2);
		addch('*');
		move(y, (max_col/2) + strlen(option[i])/2 + 2);
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
	  else if(cur_position > 6)
		cur_position %= 7;
	  
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