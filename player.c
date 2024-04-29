/* player.c */
#include <stdlib.h>			/* malloc() */
#include <string.h>			/* memset() */
#include <unistd.h>			//open() close()
#include <fcntl.h>			//file options O_RDONLY e.t.c.

#include "mapping.h"		/* defines MAP_ROWS */
#include "list.h"			/* compare() */
#include "file.h"			/* err_sys() concatinate_path() mmap_user() */

/* Progress */
struct progress {
	//Name of the campaign file whithout path and extention.
	char *FileName;
	//The last round is not finished yet
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

int pick_up_prog(char *player_name, char *campaign_name, struct progress *saved_camp){
	
}
//File descripror will be changed
int add_prog(char *player_name, char *campaign_name, int *file_descriptor){
  
  return 0;
}

int remove_prog(char *player_name, char *campaign_name, int *file_descriptor) {
  
  return 0;
}

int change_prog(char *player_name, char *campaign_name, const int *file_descriptor) {
  
  return 0;
}
/*  */
int load_prog(){
	
}

/* Saves sruct player in the file */
static int create_player(char *player_name) {
	char *file_name;
	char *path = "./players/";
	char *extention =".pplayer"
	int file_descriptor;
	int len
	struct player *current_player;
	
	len = sizeof(struct player*);
	current_player = malloc(len);
	file_name =	malloc(260);
	concatinate_path(path, player_name, extention, file_name, 260)
	memset(current_player -> name, 0, 50); 			/* REWRITE 50 */
	memset(current_player -> progress_list, 0, sizeof(current_player -> progress_list));
	strcat(current_player -> name, player_name);	/* Set name */

	file_descriptor = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0666);
	free(file_name);
	if(file_descriptor == -1)
	  err_sys("while open file for writing!", -1);
	else if(len != write(file_descriptor, current_player, len))
	  err_sys("Error while writing in file!", -1);
	if (close(file_descriptor) == 0)
	  perror("File closed with errors!");
	
	return 0;
}

//Stash progress
static int save_progress(char* campaign_name, char *player_name, int rnd, int map[MAP_ROWS][MAP_ROWS], int scr){
  struct player *tmp;
  tmp = malloc(sizeof struct player);
  int offset, len
  len = sizeof(struct progress);
  offset = sizeof(struct player); /* File consist of struct player + structs of progress */
  void *data
  rewrite_data(int offset, int len, void *data, "./players/", char *file_name, ".player");
  
  
  return 0;
}
