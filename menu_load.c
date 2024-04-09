/* menu_load.c */
#include <ncurses.h> 		//clear(),mvprintw();
#include <string.h>
#include "file.h"
#include <stdlib.h>

/* load campaign from the file */
int ld_cmp(){
	struct f_list *camp;
	camp = ls_dr(".");
	clear();
	for(int i=0; camp; i++){
	  move(2+i,10);
	  printw("%d %s", camp -> count, camp -> file_name);
	  camp = camp -> next; 
	}
	getch();
	return 0;
}


