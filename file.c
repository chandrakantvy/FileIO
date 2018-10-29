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
	file *fp = (file *)malloc(sizeof(file));
	/*if(*mode != 'w' && *mode != 'r' && *mode != 'a')
		return NULL; */
	/*for(fp = arrfile; fp < arrfile + MAX_FILE; fp++)
		if((fp->flag & READ | WRITE) == 0)
			break;  */                    // file space is found
			
	//if(fp >= arrfile + MAX_FILE)       //file array is full
	//	return NULL; 

	if(!strcmp(mode, "w+")) {
		fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, PERM);
		flag = READ | WRITE;
	}	
	else if (!strcmp(mode, "a+")) {
		fd = open(filepath, O_RDWR | O_CREAT | O_APPEND, PERM);
		flag = READ | WRITE;
	}
	else if(!strcmp(mode, "r+")) {
		fd = open(filepath, O_RDWR);
		flag = READ | WRITE;
		
	}
	else if(!strcmp(mode, "w")) {
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, PERM);
		flag = WRITE;
	}
	else if(!strcmp(mode, "a")) {
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, PERM);
		flag = WRITE;
	}
	else if(!strcmp(mode, "r")) {
		fd = open(filepath, O_RDONLY);
		flag = READ;
	}
	else {
		fd = -1;
		flag = _ERR;
		return NULL;
	}
	if(fd == -1)
		return NULL;
	fp->fd = fd;
	fp->flag = flag;
	fp->count = 0;
	fp->base = fp->next = NULL;
	if(strcmp(mode, "a+") || strcmp(mode, "r"))
		fillbuff(fp);
	return fp; 
}

size_u Fwrite(void *buf, size_u size, size_u nmemb, file *fp) {
	int i;
	size_u x, sum = 0;
	void *buffer = buf;
	for(i = 0; i < nmemb; i++) {
		x = write(fp->fd, buffer, size);
		if(!x)
			break;
		buffer = buffer + size;	
		sum = sum + x;		
	}
	fillbuff(fp);	
	return sum;	
}
/*
size_u Fread(void *buf, size_u size, size_u nmemb, file *fp) {
	

} */

void fillbuff(file *fp) {
	int buffsize;
	if((fp->flag & (READ | _EOF | _ERR)) != READ) {
		return;
	}
	
	buffsize = (fp->flag & UNBUF) ? 1 : BUFFSIZE;
	
	if(fp->base == NULL)
		if((fp->base = fp->next = (char *)malloc(buffsize)) == NULL)
			return;
	if(!(fp->count))
		fp->base = fp->next;
	fp->count = read(fp->fd, fp->next, buffsize);
	fp->next = fp->next + fp->count;
	*(fp->next) = '\0';
}
















