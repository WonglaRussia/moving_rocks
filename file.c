/* file.c */
#include <stdio.h>			//fputc() fgetc()
#include <stdlib.h>			//exit()
#include <errno.h>			//perror()
#include <unistd.h>			//open() close() lseek() fsync()
#include <fcntl.h>			//file options O_RDONLY e.t.c.
#include <sys/types.h>
#include <dirent.h>			//opendir(), readdir()
#include <stdlib.h>			//malloc()
#include <string.h>			//strcpy()
#include <ncurses.h>
#include "list.h"			//struct list; chck_ls();

#include "mapping.h"		//define MAP_ROWS
#define SIZE_OF_A_MAP 2500	//bytes (int size) * MAP_ROWS ^ 2 REWRITE

/* pointer to data, foleder path like "./maps/" extention like ".rrmap" */
int append_data(void *pointer, int len, char *folder_path, char *file_name, char *extention){
	int file_descriptor;
	char *full_name = malloc(260);
	
	memset(full_name, 0, 260); /* REWRITE check if it is not necessary */
	strcat(full_name, folder_path);
	strcat(full_name, file_name);
	strcat(full_name, extention);
	
	file_descriptor = open(full_name, O_RDWR | O_CREAT | O_APPEND | O_NONBLOCK, 0666);
	if (file_descriptor == -1 ) {
		perror("Erorr occured while opening the file");
		close(file_descriptor);
		free(full_name);
		return -1;
	}
	else if(len != write(file_descriptor, pointer, len)){
		perror("Erorr occured while writing to the file");
		close(file_descriptor);
		free(full_name);
		return -1;
	}
	fsync(file_descriptor);
	close(file_descriptor);
	free(full_name);
	return 0;
}

//Loads the map from the file to current_map. The first round is 0.
int load_map(int current_map[][MAP_ROWS], char *file_name, const int round_number){
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

// Retrives list of files from dr_nm (directory name).
struct list* ls_dr(const char *dr_nm, const char *pattern){
	struct list *first = NULL, *last = NULL, *tmp;
	struct dirent *fl;
	DIR *dir;
	dir = opendir(dr_nm);
	if(!dir) {
		perror("Can`t open dir");
		return NULL;
	}
	while((fl = readdir(dir))) {
	  if(fl -> d_type == DT_REG){
		if(!(tmp = malloc(sizeof(struct list))))
			exit(1);
		tmp -> content = malloc(256);
		strcpy(tmp -> content, fl -> d_name);
		tmp -> next = NULL;
		if(first) {
		  last -> next = tmp;
		  last = last -> next;
		} else {
		  first = last = tmp;
		}
	  }
	}
	closedir(dir);
	first = chck_ls(first, pattern);
	return first;
}


// Rewrite the file partially, offset from the file begining. -1 - error.
int rewrite_data(int offset, int len, void *data, char *folder, char *file_name, char *extention) {
	int file_descriptor();
	char full_name[260];
	memset(full_name, 0, 260);
	strcat(full_name, folder);
	strcat(full_name, file_name);
	strcat(full_name, extention);
	
	if((file_descriptor = open(file_name, O_RDWR | O_CREAT | O_NONBLOCK)) == -1) {
		perror("Can`t open the file.");
		close(file_descriptor);
		return -1;
	}
	lseek(file_descriptor, offset, SEEK_SET);
	if (len != write(file_descriptor, data, len)) {
		perror("Error in writing to the file!");
		close(file_descriptor);
	}
	close (file_descriptor);
	return 0;
}