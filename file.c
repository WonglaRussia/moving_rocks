/* file.c */
#include <stdio.h>			//fputc() fgetc()
#include <stdlib.h>			//exit()
#include <errno.h>			//perror()
#include <unistd.h>			//open() close() lseek()
#include <fcntl.h>			//file options O_RDONLY e.t.c.
#include <sys/types.h>
#include <dirent.h>			//opendir(), readdir()
#include <stdlib.h>			//malloc()
#include <string.h>			//strcpy()

#include "mapping.h"		//define MAP_ROWS
#define SIZE_OF_A_MAP 2500	//bytes (int size) * MAP_ROWS ^ 2
#define RRMAP .rrmap

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

//list of filenames;
struct f_list {
	char *file_name;
	struct f_list *next;
};


// 1 = match;
static int compare(const char pattern[], const char string[]){
	if(pattern[0] == 0)
	  return 1; 	/* walked through all the pattern already */
	else
	  if(pattern[0] == string[0]) {
	    if(compare(pattern+1, string+1) == 1)
	      return 1; /* try to check all the pattern */
	} 
	else 
      if(string[0] == 0)
	    return 1;
	return compare(pattern, string+1);
}
	
//exclude from list by pattern
struct f_list* chck_ls(struct f_list *raw_list) {
  struct f_list *first, *prew = NULL, *tmp, *current;
  char *string;
  first = current = raw_list;			/* begin of list */
  while(current){ 						/* != NULL */
    string = current -> file_name;		/* set file name */
    if(compare(".rrmap", string) == 0){ /* not rrmap */
      if(prew)							/* prew != NULL */
  	    prew -> next = current -> next;	  
      if(current == first)				
  	    first = first -> next;			/* removes first record */
  	  tmp = current;
  	  current = current -> next;
  	  free(tmp);		
    } else {							/* just move further */
      prew = current;
      current = current -> next;
    }
  }
  return first;
}

// Retrive list of files from dr_nm (directory name) to ls_dr.
struct f_list* ls_dr(const char *dr_nm) {
	struct f_list *first = NULL, *last = NULL, *tmp;
	struct dirent *fl;
	DIR *dir;
	dir = opendir(dr_nm);
	if(!dir) {
		perror("Can`t open dir");
		return NULL;
	}
	while((fl = readdir(dir))) {
	  if(fl -> d_type == DT_REG){
		if(!(tmp = malloc(sizeof(struct f_list))))
			exit(1);
		tmp -> file_name = malloc(256);
		strcpy(tmp -> file_name, fl -> d_name);
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
	tmp = first;
	first = chck_ls(tmp);
	return first;
}
