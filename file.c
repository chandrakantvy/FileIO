#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "file.h"

file *Fopen(char *filepath, char *mode) {
	int fd, flag;
	file *fp;
	if(*mode != 'w' && *mode != 'r' && *mode != 'a')
		return NULL;
	for(fp = arrfile; fp < arrfile + MAX_FILE; fp++)
		if((fp->flag & READ | WRITE) == 0)
			break;                      // file space is found
			
	if(fp >= arrfile + MAX_FILE)       //file array is full
		return NULL; 

	if(strcmp(mode, "w+")) {
		fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, PERM);
		flag = READ | WRITE;
	}	
	else if (strcmp(mode, "a+")) {
		fd = open(filepath, O_RDWR | O_CREAT | O_APPEND, PERM);
		flag = READ | WRITE;
	}
	else if(strcmp(mode, "r+")) {
		fd = open(filepath, O_RDWR, 0);
		flag = READ | WRITE;
	}
	else if(strcmp(strcmp(mode, "w")) {
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, PERM);
		flag = WRITE;
	}
	else if(strcmp(mode, "a")) {
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, PERM);
		flag = WRITE;
	}
	else if(strcmp(mode, "r")) {
		fd = open(filepath, O_RDONLY, 0);
		flag = READ;
	}
	else {
		fd = -1;
		flag = ERR;
		return NULL;
	}
	if(fd == -1)
		return NULL;
	fp->fd = fd;
	fd->flag = flag;
	fp->count = 0;
	fp->base = fp->next = NULL;
	return fp;
}


