/* rolling-the-rocks.c */
#include <string.h>						//to set string address
#include <ncurses.h>

#include "maps.h"						//current_map
#include "rocks.h"						//play_the_map()
#include "file.h"						//append_map_to_the_file();
										//extract_map();

#define FILE_N_MAPS "Rolling_maps.rrmap"//maps chain

char work_bw;							//b&w terminal?


int main() {
//WRITE writing the map to file
//WRITE reading the map from the file
	int *round_number;					//to calculate offcet if the file while reading the map
	char filename_with_maps[] = FILE_N_MAPS;					//set the filename [1, infinity]
	
	
	score = 40;
	//append_map_to_the_file(current_map, filename_with_maps); 	//append the map to the file
	initscr();
	work_bw = !has_colors();						//REWRITE all screen functions
	keypad(stdscr, 1); 								//esc seq for moving by arrows
	curs_set(0);
	*round_number = 1;
	for(; extract_map(current_map, filename_with_maps, round_number) ; *round_number++) {
		play_the_map(current_map);
	}
	endwin();
return 0;
}
