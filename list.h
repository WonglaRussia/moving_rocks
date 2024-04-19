/* list.h */
#ifndef L_LISTS_H
#define L_LISTS_H
struct list {
	char *content;
	struct list *next;
};
//returns quantity of nodes in the list
int count_list(struct list *first);
//free the allocated memory
int free_list(struct list *flist);
//excludes nodes not containing the pattern in contetnt record.
struct list* chck_ls(struct list *raw_list, const char * pattern);
/* Just create the list of options 
 * use char* as function param */
struct list* form_list(int qt, ...);
//Return the content of the pointed inode (serial [ 0; quantity of inodes - 1 ])
char* retrive_content(int serial, struct list *first);
// if the pattern is in the string; 1 = match;
int compare(const char *pattern, const char *string);
#endif