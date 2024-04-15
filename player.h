/* player.h */
#ifndef PLAYER_H
#define PLAYER_H
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
#endif