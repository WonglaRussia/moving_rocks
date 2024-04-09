/* menu_load.c */
#include <ncurses.h> 		//clear(),mvprintw();
#include <string.h>
#include "file.h"

/* load campaign from the file */
int ld_cmp(){
	struct f_list *camp;
	camp = ls_dr("C:\\Users\\asanov\\Desktop\\GITHUB\\moving_rocks\\");
	clear();
	for(int i=0; camp; i++){
	  char *text;
	  text = camp -> file_name;
	  move(2+i,10);
	  printw("%s", text);
	  camp = camp -> next; 
	}
	getch();
	return 0;
}