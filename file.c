/* file.c */
#include <stdio.h>			//fputc() fgetc()
#include <stdlib.h>			//exit()
#include <errno.h>			//perror()
#include <unistd.h>			//open() close() lseek() fsync()
#include <fcntl.h>			//file options O_RDONLY e.t.c.
#include <sys/types.h>
#include <sys/stat.h>		/* mmap() */
#include <dirent.h>			//opendir(), readdir()
#include <stdlib.h>			//malloc()
#include <string.h>			//strcpy()
#include <ncurses.h>
#include "list.h"			//struct list; chck_ls();

#include "mapping.h"		//define MAP_ROWS
#define SIZE_OF_A_MAP 2500	//bytes (int size) * MAP_ROWS ^ 2 REWRITE

void err_sys(const char* x, int err_no){
    perror(x);
    return err_no;
}

/*  */
void concatinate_path(char *folder_path, char *file_name, char *extention, char *full_name, int len) {
	memset(full_name, 0, len);
	strcat(full_name, folder_path);
	strcat(full_name, file_name);
	strcat(full_name, extention);
	return;
}

/* pointer to data, foleder path like "./maps/" extention like ".rrmap" */
int append_data(void *pointer, int len, char *folder_path, char *file_name, char *extention){
	int file_descriptor;
	char *full_name = malloc(260);
	
	concatinate_path(folder_path, file_name, extention, full_name, 260);
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

/* MAP player file to the memory location.
 * File descriptor == NULL if file is not opened yet*/
struct player* mmap_user(char *user_name, int *file_descriptor){
	char *path = "./players/";
	char *extention = ".pplayer";
	char *full_f_name[260];
	int page_size, len;
	struct stat *file_stat;
	struct player *tmp_player;
	
	file_stat = malloc(sizeof(struct stat));
	concatinate_path(folder, user_name, extention, full_name, 260);
	
	if(!file_descriptor) {
	  if ((*file_descriptor = open(full_f_name, O_RDWR | O_CREAT | O_APPEND | O_NONBLOCK, 0666)) == -1) 
	    err_sys("Error while opening the player file", -1)
	}
	
	fstat(*file_descriptor,file_stat);
	
	page_size = getpagesize();
	len = ((file_stat -> st_size) / page_size + 1) * page_size;
	 
	tmp_player = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, *file_descriptor, 0);
	if (tmp_player == MAP_FAILED)
	  err_sys("Error while mapping player file");
	free(file_stat);
	return tmp_player;
}