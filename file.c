/* file.c */
#include <stdio.h>			//fputc() fgetc()
#include <stdlib.h>			//exit()
#include <errno.h>			//perror()
#include "mapping.h"		//define MAP_ROWS

int append_map_to_the_file(int current_map[][MAP_ROWS], char *file_name)
{
	FILE *f;
	f = fopen(file_name, "ab");
	if(!f){
		perror("file");
		exit(1);
	}
	int y, x;
	for(y = 0; y < MAP_ROWS; y++){
	  for(x=0; x < MAP_ROWS; x++){
		fputc(current_map[y][x] , f);
	  }
	}
	fflush(f);
	fclose(f);
	return 0;
}

int extract_map(int current_map[][MAP_ROWS], char *file_name, int *round_number)
{
	FILE *f;
	if(!f){
		perror("file");		//REWRITE filename to global
		exit(1);
	}
	int y, x;
	for(y = 0; y < MAP_ROWS; y++){
	  for(x=0; x < MAP_ROWS; x++){
		if(current_map[y][x] == EOF)		//there is no another map in the file
		  return 100;
		current_map[y][x] = fgetc(f);
	  }
	}
	fclose(f);
	return 0;
}
