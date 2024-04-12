/* main.c */
#include <string.h>						//to set string address
#include <ncurses.h>					//here we initialize the screen
#include <stdlib.h>

#define FILE_N_MAPS "vava_campaign.rrmap"//default map chain

#include "list.h"						//struct list.
#include "menu.h"						//int menu();
#include "menu_start.h"					//int start_game();
#include "menu_map_editor.h"			//int edit();
#include "menu_load.h"					//int ld_cmp();

int main(){
	int choosen_position;
	struct list *options;
	initscr();
	keypad(stdscr, 1); 					/*esc seq for moving by arrows*/
	curs_set(0);
	options = form_list(7,"Continue","Start","Load_Charachter","Save","Map_Editor","Play_on-line","Exit");
	for(;;){
	  choosen_position = menu(options); 
	  switch(choosen_position) {
	  case(0):	{ if(start_game(FILE_N_MAPS) == 1){getch(); endwin();}	break;} /* Continue */
	  case(1): 	{ if(start_game(FILE_N_MAPS) == 1) endwin();	break;}		/* Start */
	  case(2): 	{ load_cmp();	endwin(); break;}								/* Load_Charachter */
	  case(3):   break;			 										/* Save */
	  case(4):	{ if( edit() == 1 ) endwin(); 		break;}			/*  Map_Editor */
	  case(5):	break;
	  case(6): 	{endwin(); exit(0);} 					/* Exit */
	  }
	}
endwin();
return 0;
}