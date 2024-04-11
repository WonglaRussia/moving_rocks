/* menu.c */
#include <ncurses.h>
#include <string.h> /* strlen() */
#include <stdarg.h> /* va_list va_start() va_arg() va_end() */
#include <stdlib.h> /* malloc() free() */

struct menu_option {
	char *option_name;
	struct menu_option *next;
};

/* 
 * static void draw_menu (int qt, int cur_pos, struct menu_option *options) 
 * qt - how many meny options
 * cur_pos - current option 
 */
static void draw_menu (int qt, int cur_pos, struct menu_option *options) {
	int m, y, max_row, max_col, fst_ln;	// fst_ln = the first line
	//int high = qt;		//? ?! 2 rows per option ?
	char *name; 
	struct menu_option *tmp;
	tmp = options;
	getmaxyx(stdscr, max_row, max_col);
	fst_ln = (max_row / 2) - (qt / 2);		
	clear();
	
	for(int i = 0; i < qt ; i++ ) {
	  name = tmp -> option_name;
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
int menu(int qt, ...) {
	//REWRITE? (potentionaly it can be global)
	int input;
	int cur_pos;
	struct menu_option *options = NULL;
	va_list option;
	va_start(option, qt); /* set pointer at 1st param*/
	{ /* Just create the list of options */
	  struct menu_option *tmp, *prew = NULL;
	  for(int i = 0; i < qt; i++) {
		tmp = malloc(sizeof(struct menu_option));
		tmp -> option_name = malloc(100);
		strcpy (tmp -> option_name, va_arg(option, char*));
		tmp -> next = NULL;
		if(!options)
		  options = tmp; /* points at the first node in the list */
		if(prew)		 /* is prew not NULL already ? */
		  prew -> next = tmp; 
		prew = tmp;		/*  */
	  }
	}
	cur_pos = 0;
	
	for(;;){
	  if(cur_pos < 0)
		cur_pos = qt - 1;
	  else if(cur_pos > qt - 1)
		cur_pos = 0; 
 	  
	  draw_menu (qt, cur_pos, options);
	  
	  input = getch();
	  switch(input){
	  case(KEY_UP):		{ --cur_pos; break;}
	  case(KEY_DOWN):	{ ++cur_pos; break;}
	  case('\n'):{
		while(options){ /* deallocate mem */
		  struct menu_option *tmp;
		  tmp = options;
		  options = options -> next;
		  free(tmp);
		}
		return cur_pos;
	  }
	  default: ;
	  }
	}
}