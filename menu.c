/* menu.c */
#include <ncurses.h>
#include <string.h> /* strlen() */
#include <stdarg.h> /* va_list va_start() va_arg() va_end() */
#include <stdlib.h> /* malloc() free() */

#include "list.h" 	/* struct list */

// qt - how many meny options, cur_pos - current option 
static void draw_menu(int qt, int cur_pos, struct list *options) {
	int m, y, max_row, max_col, fst_ln;	// fst_ln = the first line
	//int high = qt;		//? ?! 2 rows per option ?
	char *name; 
	struct list *tmp;
	tmp = options;
	getmaxyx(stdscr, max_row, max_col);
	fst_ln = (max_row / 2) - (qt / 2);		
	clear();
	for(int i = 0; i < qt ; i++ ) {
	  name = tmp -> content;
	  y = fst_ln + i;
	  //print the option
	  move(y, (max_col / 2) - (strlen(name)/2) );
	  printw("%s", name);
	  if(i == cur_pos) {
		//print left asteriks *
		move(y, (max_col/2) - strlen(name)/2 - 2);
		addch('*');
		//only to align gap among the end of the text and asteriks *
		if((strlen(name) % 2) != 0) { 
		  m = 2; 
		} else m = 1;
		//print right asteriks *
		move(y, (max_col/2) + strlen(name)/2 + m);
		addch('*');
	  }
	  tmp = tmp -> next;
	}	
	refresh();
}
// draw menu and returns the number of the choosen option
int menu(struct list *options){
	int input;
	int qt, cur_pos; /* quantity, current_position */
	qt = count_list(options);
	cur_pos = 0;
	for(;;){
	  if(cur_pos < 0)
		cur_pos = qt - 1;	/* [0,(qt-1)] */
	  else if(cur_pos > qt - 1)
		cur_pos = 0;
	
	  draw_menu(qt, cur_pos, options);
	  input = getch();
	  switch(input){
	  case(KEY_UP):		{ --cur_pos; break; }
	  case(KEY_DOWN):	{ ++cur_pos; break; }
	  case('\n'):		return cur_pos;
	  default: ;
	  }
	}
}