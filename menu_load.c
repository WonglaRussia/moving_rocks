/* menu_load.c */
#include <ncurses.h> 		/* clear(),mvprintw(); */
#include <string.h>
#include "file.h"			/* ls_dr(); struct f_list->f_list */
#include <stdlib.h>

/* load campaign from the file */
int ld_cmp(){
	struct f_list *camp;
	camp = ls_dr("./maps",".rrmap");
	clear();
	for(int i=0; camp; i++){
	  move(2+i,10);
	  printw("%s", camp -> file_name);
	  camp = camp -> next; 
	}
	getch();
	free_f_list(camp);
	return 0;
}


