/* player.c */

#include <stdlib.h>			/* malloc() */

#include "mapping.h"		/* defines MAP_ROWS */


/*
 *Player	.Name
 *			.Progress (struct)
 *			.Next (player)
./saves/*.pplayer
create_player() rename_player() remove_player() set_player()

(file.c) 

 *Progress	.FileName
 *			.LastMap
 *			.Round
 *			.CampaignScore
 *			.Next
save_game(add_campaign_progress_and_if_exists_change)
continue_campaign()


*Change Player	(Choose Player (change current player, New Player)
*Quick Play 	(visual choose the map map by map camp by camp OR random play)
*Play Campaign

start_game(char *camp_name, struct player *current_player)
*/
/* 
Progress contains point where users finished compaign 
To continue camp lately
*/
struct progress {
	char *FileName;
	unsigned int round;
	int last_map[MAP_ROWS][MAP_ROWS];
	int CampaignScore;
	struct progress *next;
}
/*
Player contains list of progress (campaigns)
*/
struct player {
	char *name;
	struct progress *progress_list;
	struct player *next;
}

int create_player(char *player_name) {
	struct player *tmp;
	tmp = malloc(sizeof(struct player));
	tmp -> name = *player_name;
	tmp -> progress = NULL;
	if (save_player(tmp) = 1){
	  //...
	  free(tmp);
	  return 1;
	}
	free(tmp);
	return 0;
}
