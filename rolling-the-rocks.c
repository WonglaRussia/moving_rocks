/* rolling-the-rock.c */
#include <string.h>						//to set string address
#include <ncurses.h>					//here we initialize the screen
#include <stdlib.h>

#include "menu.h"						//int menu();
#include "menu_start.h"					//int start_game()
#include "menu_map_editor.h"			//int edit();
	//enum position { Continue,Start,Load_Charachter,Save,Map_Editor,Play_on_line,Exit };
//#include "maps.h"						//current_map (REWRITE to malloc?)

//#include "file.h"						//append_map_to_the_file();
										//extract_map();



char work_bw;							//b&w terminal?

int main() {
	enum position choosen_position;
	
	initscr();
	work_bw = !has_colors();				//REWRITE all screen functions?
	keypad(stdscr, 1); 						//esc seq for moving by arrows
	curs_set(0);

	for(;;){		//REWRITE to forever while added options
	  choosen_position = menu();
	  switch(choosen_position) {
	  case(Continue):			{ if(start_game() == 1) endwin();	break;}
	  case(Start): 				{ if(start_game() == 1) endwin();	break;}
	  case(Load_Charachter): 	break;			
	  case(Save):     break;			// 
	  case(Map_Editor): break;	//
	  case(Play_on_line):break;
	  case(Exit): 				{endwin(); exit(0);}
	  }
	}
endwin();
return 0;
}
