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
	if(strcmp(mode, "w+")){
		fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, PERM);
		flag = O_RDWR | O_CREAT | O_TRUNC;
	}	
	else if (strcmp(mode, "a+")) {
		fd = open(filepath, O_RDWR | O_CREAT | O_APPEND, PERM);
		flag = O_RDWR | O_CREAT | O_APPEND;
	}
	else if(strcmp(mode, "r+")) {
		fd = open(filepath, O_RDWR, PERM);
		flag = O_RDWR;
	}
	else if(strcmp(strcmp(mode, "w")) {
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, PERM);
		flag = O_WRONLY | O_CREAT | O_TRUNC
	}
	else if(strcmp(mode, "a")) {
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, PERM);
		flag = O_WRONLY | O_CREAT | O_APPEND;
	}
	else if(strcmp(mode, "r")) {
		fd = open(filepath, O_RDONLY, 0);
		flag = O_RDONLY;
	}
	else {
		fd = -1;
		flag = 0;
		return NULL;
	}
	if(fd == -1)
		return NULL;
	fp->fd = fd;
	fd->flag = flag;
	return fp;
}


