/* file.h */
#include "mapping.h"				//define MAP_ROWS
#ifndef G_FILE_H
#define G_FILE_H
int append_map_to_the_file(int current_map[][MAP_ROWS], char *file_name);
int extract_map(int current_map[][MAP_ROWS], char *file_name, int *round_number);
#endif