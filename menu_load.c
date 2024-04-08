/* menu_load.c */
#include <ncurses.h> 		//clear(),mvprintw();
#include <string.h>
#include "file.h"

int load_camp(){
	char list[][255];
	if (list_campaing(list) == 1) {
		mvprintw(10,10,"%s","Cant read directory content.");
		getch();
		return 1;
	}
	else clear();
	mvprintw(10,10,"%s","CAN read directory content.");
	getch();
	return 0;
}