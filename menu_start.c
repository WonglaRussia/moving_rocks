/* menu_start.c */
#include "file.h"		//load_map()
#include "round.h"		//play_the_map(); extern int score
#include "mapping.h"	//define MAP_ROWS
#define FILE_N_MAPS "vava_campaign.rrmap"//default map chain

//REWRITE to user structure with filename,round,name,id. To load/save/continue
//the game with the same function

/*	In cycle we load the map from the file and play it.
	If EOF (all maps are played) return 1	*/

int start_game(){
	int current_map[MAP_ROWS][MAP_ROWS];
	int round;									//to calculate offset in loading the map REWRITE
	char filename_with_maps[] = FILE_N_MAPS; 	//set the filename [1, infinity]
	for(round = 0; ; round++){
		if ( round == 0)
			score = 40;
		if ( load_map(current_map, filename_with_maps, round) != 0 ) {
			return 1;
		}
		play_the_map(current_map);
	}
}