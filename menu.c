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
	int corner_y;			//start of the option line
	int high = 3 * 7;		//only 3 rows for each 6 options (REWRITE?)
	int i;
	int m;
	getmaxyx(stdscr, max_row, max_col);
	//here y is the left position of the menu
	corner_y = (max_row / 2) - (high / 2);		
	
	clear();
	for(i = 0; i < 7 ; i++ ) {
	  y = corner_y + i;
	  //print the option
	  move(y, (max_col / 2) - (strlen(option[i])/2) );
	  printw("%s", option[i]);
	  if(i == current_position) {
		//print left asteriks *
		move(y, (max_col/2) - strlen(option[i])/2 - 2);
		addch('*');
		
		//only to align gap among the end of the text and asteriks *
		if((strlen(option[i]) % 2) != 0) { m = 2; } 
		else m = 1;
		//print right asteriks *
		move(y, (max_col/2) + strlen(option[i])/2 + m);
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
	  if(cur_position < 0) //!!REWRITE it is ENUM
		cur_position = 6;
	  else if(cur_position > 6)
		cur_position = 0; 
	  
	  draw_menu(cur_position);
	  
	  input = getch();
	  switch(input){
	  case(KEY_UP):{ 
	    --cur_position;
		break;
	  }
	  case(KEY_DOWN):{
		++cur_position;
		break;
	  }
	  case('\n'):
	    return cur_position;
	  default: ;
	  }
	}
}