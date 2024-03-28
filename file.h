/* file.h */
#include "mapping.h"				//define MAP_ROWS
#ifndef G_FILE_H
#define G_FILE_H
#define FILE_N_MAPS "Rolling_maps.rrmap"//maps chain
int append_map_to_the_file(int current_map[][MAP_ROWS], char *file_name);
int load_map(int current_map[][MAP_ROWS], char *file_name, const int round_number);
#endif