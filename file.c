/* file.c */
#include <stdio.h>			//fputc() fgetc()
#include <stdlib.h>			//exit()
#include <errno.h>			//perror()
#include <unistd.h>			//open() close() lseek()
#include <fcntl.h>			//file options O_RDONLY e.t.c.
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>		//malloc

#include <string.h>

#include "mapping.h"		//define MAP_ROWS
#define SIZE_OF_A_MAP 2500	//bytes (int size) * MAP_ROWS ^ 2

int append_map_to_the_file(int current_map[][MAP_ROWS], char *file_name)
{
	int file_descriptor;
	int len = SIZE_OF_A_MAP;
	
	file_descriptor = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file_descriptor == -1 ) {
		close(file_descriptor);
		return -1;
	}
	else if(len != write(file_descriptor, current_map, SIZE_OF_A_MAP)){
		perror("while writing to the file");
		close(file_descriptor);
		return -1;
	}
	if (close(file_descriptor) == 0)
		perror("File closed with warnings.");
	return 0;
}

//Round number offsets reading map by map. The first round is 0
int load_map(int current_map[][MAP_ROWS], char *file_name, const int round_number)
{
	int file_descriptor;
	int len = SIZE_OF_A_MAP;
	
	file_descriptor = open(file_name, O_RDONLY);
	if (file_descriptor == -1 ) {
		perror("while open file for reading");
		return -1;
	}
	else {
		lseek(file_descriptor, SIZE_OF_A_MAP * round_number, SEEK_SET);
		if (len != read(file_descriptor, current_map, SIZE_OF_A_MAP)){
			perror("Error while reading the file\n");
			close(file_descriptor);
			return -1;
		}	
	}
	close(file_descriptor);
	return 0;
}

struct f_list {
	int count;
	char *file_name;
	struct f_list *next;
};

// Retrive list of filest from dr_nm (directory name) to ls_dr.
struct f_list* ls_dr(const char *dr_nm) {
	struct f_list *first = NULL, *last = NULL, *tmp;
	struct dirent *fl;
	DIR *dir;
	dir = opendir(dr_nm);
	if(!dir) {
		perror("Can`t open dir");
		return NULL;
	}
	int i = 0;
	while((fl = readdir(dir))) {
	  if(fl -> d_type == DT_REG){
		if(!(tmp = malloc(sizeof(struct f_list))))
			exit(1);
		tmp -> count = i;
		tmp -> file_name = fl -> d_name;
		tmp -> next = NULL;
		if(first == NULL) {
		  first = last = tmp;
		} else {
		  last -> next = tmp;
		  last = last -> next;
		}
	  }
	}
	closedir(dir);
	return first;
}
