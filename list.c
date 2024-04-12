/* list.c */
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

//list
/* 
struct f_list {
	char *file_name;
	struct f_list *next;
}; 
*/
struct list {
	char *content;
	struct list *next;
};
//resturns quantity of files in directory;
//int count_f_list(struct list *first)
int count_list(struct list *first){
	struct list *tmp;
	int i;
	tmp = first;
	if(!first)
	  return 0;
	for(i = 0; tmp; i++) 
	  tmp = tmp -> next;
	return i;
}
//free the file list mem
//int free_f_list(struct list *flist) 
int free_list(struct list *flist) {
	struct list *tmp;
	while(flist){
	  tmp = flist;
	  flist = flist -> next;
	  free(tmp);
	}
	return 0;
}
// check if the pattern is in the string; 1 = match;
static int compare(const char *pattern, const char *string){
	if(pattern[0] == 0)
	  return 1; 	/* walked through all the pattern already */
	else
	  if(pattern[0] == string[0]) {
	    if(compare(pattern+1, string+1) == 1)
	      return 1; /* try to check all the pattern */
	} 
	else 
      if(string[0] == 0)
	    return 0;
	return compare(pattern, string+1);
}
// exclude from the list by compare the name with the pattern
struct list* chck_ls(struct list *raw_list, const char * pattern) {
  struct list *first, *prew = NULL, *tmp, *current;
  char *string;
  first = current = raw_list;			/* begin of list */
  while(current){ 						/* != NULL */
    string = current -> content;		/* set file name */
    if(compare(pattern, string) == 0){ 	/* not rrmap */
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
