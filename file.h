/* file.h */
#include "mapping.h"				//define MAP_ROWS
#ifndef G_FILE_H
#define G_FILE_H
int append_map_to_the_file(int current_map[][MAP_ROWS], char *file_name);
//Loads the map from the file to current_map. The first round is 0.
int load_map(int current_map[][MAP_ROWS], char *file_name, const int round_number);
struct list* ls_dr(const char *dr_nm, const char *pattern);
#endif