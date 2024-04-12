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
#endif