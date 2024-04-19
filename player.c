/* player.c */
#include <stdlib.h>			/* malloc() */
#include <string.h>			/* memset() */
#include <unistd.h>			//open() close()
#include <fcntl.h>			//file options O_RDONLY e.t.c.

#include "mapping.h"		/* defines MAP_ROWS */



/* Progress */
struct progress {
	//file name of the campaign file whithout path and extention
	char *FileName;
	//last round is not finished
	unsigned int round;
	//last map must be fetched while loading
	int last_map[MAP_ROWS][MAP_ROWS];
	//score (?REWRITE if score is common)
	int CampaignScore;
	//to enlist all progress records
	struct progress *next;
}
/* Struct Player contains name
 * and points at list of progress (campaigns)
*/
struct player {
	char *name[50];
	struct progress *progress_list;
}
/* saves player struct in file
 * to the folder ./players/
 * file name and user name both are the same
*/

/* Saves sruct player in the file */
static int save_player(struct player *current_player) {
	char *file_name;
	char *path = "./players/";
	char *extention =".pplayer"
	int file_descriptor;
	int len
	
	len = sizeof(struct player*);
	file_name =	malloc(260);
	memset(file_name, 0, sizeof(file_name)); /* REWRITE check if it is not necessary */
	
	/* path(folder) + file name + file extention */
	strcat(file_name, path);
	strcat(file_name, current_player -> name);
	strcat(file_name, extention);
	/* Open to write */
	file_descriptor = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
	
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
	return 0;
}

int create_player(char *player_name) {
	struct player *tmp;
	tmp = malloc(sizeof(struct player));
	tmp -> name = *player_name;
	tmp -> progress = NULL;
	if (save_player(tmp) = 0){
	  free(tmp);
	  return 1;
	}
	free(tmp);
	return 0;
}

static int add_progress(char *player_name, int rnd, int map[MAP_ROWS][MAP_ROWS], int scr){
  struct player *tmp; 
  tmp = malloc(sizeof struct player);
  
  return 0;
}
static remove_progress(char *player_name, char *campaign_name) {
  
  return 0;
}
