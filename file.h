/* file.h */
#include "mapping.h"				//define MAP_ROWS
#ifndef G_FILE_H
#define G_FILE_H
/* pointer to data, foleder path like "./maps/" extention like ".rrmap" */
int append_data(void *pointer, int len, char *folder_path, char *file_name, char *extention);
//Loads the map from the file to current_map. The first round is 0.
int load_map(int current_map[][MAP_ROWS], char *file_name, const int round_number);
// Retrives list of files from dr_nm (directory name).
struct list* ls_dr(const char *dr_nm, const char *pattern);
// Rewrite the file partially (also create file), offset from the file begining. -1 - error.
int rewrite_data(int offset, int len, void *data, char *folder, char *file_name);
#endif