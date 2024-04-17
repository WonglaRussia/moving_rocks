/* player.c */


#include <stdlib.h>			/* malloc() */
#include <string.h>			/* memset() */
#include <unistd.h>			//open() close()
#include <fcntl.h>			//file options O_RDONLY e.t.c.

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
	char *name[255];
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
//declare function before
int save_player(struct player current_player) {
	char *file_name;
	char *path = "./players/";
	char *extention =".pplayer"
	int file_descriptor;
	int len
	
	file_name =	malloc(260);
	memset(file_name, 0, sizeof(file_name)); /* REWRITE check if it is not necessary */
	strcat(file_name, path);
	strcat(file_name, current_player -> name);
	strcat(file_name, extention);
	len = sizeof(struct player*);
	file_descriptor = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if(file_descriptor == -1) {
	  perror("while open file for writing!");
	  close(file_descriptor);
	  return -1;	
	} 
	else if(len != write(file_descriptor, current_player, len)){
	  perror("Error while writing in file!");
	  return -1;
	}
	if (close(file_descriptor) == 0)
	  perror("File closed with errors!");
	free(file_name);
}