/* rolling-the-rocks.c */
#include <string.h>						//to set string address
#include <ncurses.h>
#include <stdlib.h>

#include "maps.h"						//current_map
#include "rocks.h"						//play_the_map()
#include "file.h"						//append_map_to_the_file();
										//extract_map();

#define FILE_N_MAPS "Rolling_maps.rrmap"//maps chain

char work_bw;							//b&w terminal?


int main() {
	int round;							//to calculate offset in loading the map
	char filename_with_maps[] = FILE_N_MAPS;					//set the filename [1, infinity]
	int current_map[MAP_ROWS][MAP_ROWS];

    /*
	if (append_map_to_the_file(old_current_map, filename_with_maps) != 0) 	//append the map to the file
		return 1;
	*/
	
	initscr();
	work_bw = !has_colors();						//REWRITE all screen functions
	keypad(stdscr, 1); 								//esc seq for moving by arrows
	curs_set(0);
	
	for(round = 0; ; round++)
	{
		if ( round == 0)
			score = 40;
		if ( load_map(current_map, filename_with_maps, round) != 0 ) {
			endwin();
			return 1;
		}
		play_the_map(current_map);
	}
	endwin();
return 0;
}
