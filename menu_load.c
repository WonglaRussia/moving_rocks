/* menu_load.c */
#include <ncurses.h> 		/* clear(),mvprintw(); */
#include <string.h>
#include <stdlib.h>

#include "list.h"			/* struct list, free_list() */
#include "file.h"			/* ls_dr() */
#include "menu.h"		
#include "menu_start.h"		/* start_game() */

/* load campaign from the file */
	int load_cmp(){
	int choosen_position, qt;
	struct list *options,*tmp;
	char *file_name;
	file_name = malloc(260);
	options = ls_dr("./maps",".rrmap");
	tmp = options;
/* Getting the last campaign to add exit option */
	while(tmp->next){		
	  tmp = tmp -> next;
	}
	tmp -> next = form_list(1,"Main menu");
	qt = count_list(options) - 1;
	clear();	
	for(;;){
	  choosen_position = menu(options); 
	  if(choosen_position == qt)
		return 0;
	  else {
	    file_name = retrive_content(choosen_position, options);
		start_game(file_name);
	  }
	}
	free(file_name);
}