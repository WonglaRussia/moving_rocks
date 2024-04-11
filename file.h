/* file.h */
#include "mapping.h"				//define MAP_ROWS
#ifndef G_FILE_H
#define G_FILE_H
int append_map_to_the_file(int current_map[][MAP_ROWS], char *file_name);
int load_map(int current_map[][MAP_ROWS], char *file_name, const int round_number);
//Contain file names
struct f_list {
	char *file_name;
	struct f_list *next;
};
//Free memory allocated for the list
int free_f_list(struct f_list *file_list);

/* Returns list of files in the directory "dr_nm".
 * List contains the names according to "pattern" */
struct f_list* ls_dr(const char *dr_nm, const char *pattern);

int count_f_list(struct f_list *first);
#endif