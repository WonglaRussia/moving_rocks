/* file.h */
#include "mapping.h"				//define MAP_ROWS
#ifndef G_FILE_H
#define G_FILE_H
int append_map_to_the_file(int current_map[][MAP_ROWS], char *file_name);
int load_map(int current_map[][MAP_ROWS], char *file_name, const int round_number);

struct f_list {
	int count;
	char *file_name;
	struct f_list *next;
};

struct f_list* ls_dr(const char *dr_nm);
#endif