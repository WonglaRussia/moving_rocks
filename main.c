/* main.c */
#include <string.h>						//to set string address
#include <ncurses.h>					//here we initialize the screen
#include <stdlib.h>

#include "menu.h"						//int menu();
#include "menu_start.h"					//int start_game();
#include "menu_map_editor.h"			//int edit();
#include "menu_load.h"					//int ld_cmp();

int main(){
	enum position choosen_position;
	
	initscr();
	keypad(stdscr, 1); 					/*esc seq for moving by arrows*/
	curs_set(0);

	for(;;){
	  choosen_position = menu();
	  switch(choosen_position) {
	  case(Continue):			{ if(start_game() == 1){getch(); endwin();}	break;}
	  case(Start): 				{ if(start_game() == 1) endwin();	break;}
	  case(Load_Charachter): 	{ ld_cmp();	endwin(); break;}			
	  case(Save):     break;			 
	  case(Map_Editor):			{ if( edit() == 1 ) endwin(); 		break;}
	  case(Play_on_line):break;
	  case(Exit): 				{endwin(); exit(0);}
	  }
	}
endwin();
return 0;
}