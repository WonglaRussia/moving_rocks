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
#include <stdarg.h> 	/* va_list va_start() va_arg() va_end() */
struct list {
	char *content;
	struct list *next;
};
//resturns quantity of files in directory;
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
struct list* chck_ls(struct list *raw_list, const char *pattern) {
  struct list *first, *prew = NULL, *tmp, *current;
  char *string;
  first = current = raw_list;			/* begin of list */
  while(current){ 						/* != NULL */
    string = current -> content;		/* set file name */
    if(compare(pattern, string) == 0){ 	/* not pattern */
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
/* Just create the list of options 
 * use char* as function param */
struct list* form_list(int qt, ...){    
  va_list option;
  struct list *tmp, *prew = NULL, *first = NULL;
  va_start(option, qt); /* set pointer at 1st param*/
  for(int i = 0; i < qt; i++) {
	tmp = malloc(sizeof(struct list));
	tmp -> content = malloc(260); /* can be used as filename */
	strcpy (tmp -> content, va_arg(option, char*));
	tmp -> next = NULL;
	if(!first)
	  first = tmp; /* points at the first node in the list */
	if(prew)                 /* is prew not NULL already ? */
	  prew -> next = tmp;
	prew = tmp;             /*  */
  }
  return first;
}
//Return the content of the pointed inode (serial [ 0; quantity of inodes - 1 ])
char* retrive_content(int serial, struct list *first){
	struct list *tmp;
	tmp = first;
	for(int i = 0;;i++){
	  if(i==serial)
		return tmp -> content;
	  tmp = tmp -> next;
	}
}