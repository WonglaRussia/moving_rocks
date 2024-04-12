/* menu_start.c */
#include <stdlib.h>		//malloc() free()
#include <string.h>		//strcat()

#include "file.h"		//load_map()
#include "round.h"		//play_the_map(); extern int score
#include "mapping.h"	//define MAP_ROWS

//REWRITE to user structure with filename,round,name,id. To load/save/continue
//the game with the same function
/*	In cycle we load the map from the file and play it.
	If EOF (all maps are played) return 1	*/

int start_game(char *camp_name){
	int current_map[MAP_ROWS][MAP_ROWS];
	int round;									//to calculate offset in loading the map REWRITE
	char *file_name;
	char *path = "./maps/";
	file_name =	malloc(260);
	strcat(file_name, path);
	strcat(file_name, camp_name);
	for(round = 0; ; round++){
		if ( round == 0)
			score = 40;
		if ( load_map(current_map, file_name, round) != 0 ) {
			free(file_name);
			return 1;
		}
		play_the_map(current_map);
	}
}