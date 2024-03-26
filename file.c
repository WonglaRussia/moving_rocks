/* file.c */
#include <stdio.h>			//fputc() fgetc()
#include <stdlib.h>			//exit()
#include <errno.h>			//perror()
#include <unistd.h>			//open() close() lseek()
#include <fcntl.h>			//file options O_RDONLY e.t.c.

#include "mapping.h"		//define MAP_ROWS
#define SIZE_OF_A_MAP 2500

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
		lseek64(file_descriptor, SIZE_OF_A_MAP * round_number, SEEK_SET);
		if (len != read(file_descriptor, current_map, SIZE_OF_A_MAP)){
			perror("Error while reading the file\n");
			close(file_descriptor);
			return -1;
		}	
	}
	close(file_descriptor);
	return 0;
}
