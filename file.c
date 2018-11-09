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
	fp->base = fp->next = fp->var = NULL;
	if(!strcmp(mode, "a+") || !strcmp(mode, "r"))
		fillbuff(fp);
	return fp; 
}

size_u Fwrite(void *buf, size_u size, size_u nmemb, file *fp) {
	int i = 0;
	size_u x, sum = 0;
	void *buffer = buf;
	for(i = 0; i < nmemb; i++) {
		x = write(fp->fd, buffer, size);
		if(!x)
			break;
		buffer = buffer + size;	
		sum = sum + x;		
	}
	if(((fp->var - fp->next) * (fp->var - fp->base)) > 0) {
		while(fp->next != fp->var) {
			*fp->next = '\0';
			(fp->next)++;
		}
		fp->count = abs(fp->var - fp->base);	
	}
	int buffsize;
	if(fp->base == NULL)
		buffsize = checkbuff(fp);
	if(!buffsize)
		fp->base = (char *)realloc(fp->base, BUFFSIZE);
	char *str = (char *)buf;
	while(*str != '\0' && buffsize--) {
		*(fp->var) = *str;	
		if(fp->var == fp->next) {
			fp->next++;
			fp->count++;		
		}	
		fp->var++;
		str++;
		if(!buffsize)
			fp->base = (char *)realloc(fp->base, BUFFSIZE);
	}
	return sum;	
}

size_u Fread(void *buf, size_u size, size_u nmemb, file *fp) {
	size_u n = 0, x = size;
	while(nmemb--) {
		if(!Feof(fp)) 
			break;	
		read(fp->fd, &buf, size);		
		n++;
	}
	/*char *str = (char *)buf;
	while(nmemb--) {
		if(!Feof(fp))
			break;
		while(x--) {
			if(!Feof(fp))
				break;
			*str++ = *fp->var++;
		}
		n++;					
	}
	*str = '\0'; */
	//n = read(fp->fd, buf, size * nmemb);
	return n;
}

int Fseek(file *fp, long offset, int whence) {
	if(offset < 0 && whence == SEEK_SET)
		return _ERR;
	if(fp->base == NULL)
		checkbuff(fp);
	int returnvalue, count = 0;
	long n = offset > 0 ? offset : -offset;
	
	returnvalue = lseek(fp->fd, offset, whence);
	
	if(returnvalue != -1) {
		switch(whence) {
			
			case(SEEK_SET):
				fp->var = fp->base;
				while(n) {
					if(fp->var == fp->next)
						break;
				
					fp->var++;
					n--;
				}
				
				while(n--) {
					//fp->next++;
					fp->var++;
					//fp->count++;
					//*(fp->var) = '\0';
					//write(fp->fd, '\0', 1);
					
				}
				break;
				
			case(SEEK_CUR):
				if(offset >= 0) {
					while(n) {
						if(fp->var == fp->next)
							break;
						fp->var++;
						n--;
					}
					while(n--) {
						//fp->next++;
						fp->var++;
						//fp->count++;
						//*(fp->var) = '\0';
						//write(fp->fd, '\0', 1);
					}
				}
				else {
					count = 0;
					while (n) {
						fp->var--;
						n--;
						count++;
						if(fp->var == fp->base)
							break;
					}
					if(n > 0) {
						fp->var = fp->var + count;
					}
				}
				break;
				
			case(SEEK_END):
				fp->var = fp->next;
				if(offset >= 0) {
					while(n--) {
						//fp->next++;
						fp->var++;
						//fp->count++;
						//*(fp->var) = '\0';
						//write(fp->fd, '\0', 1);
					}
				}
				else {
					count = 0;
					while (n) {
						fp->var--;
						n--;
						count++;
						if(fp->var == fp->base)
							break;
					}
					if(n > 0) {
						fp->var = fp->var + count;
					}
				}
				break;
				
			default :
				return _ERR;
		}	
	}
	return returnvalue;
}

int Feof(file *fp) {
	int result = (fp->var - fp->base);
	result = result > 0 ? result : -result;
	if(result == fp->count) {             //what to use fp->count or null character to check EOF beacause their might be elements after null charecter
		return 0;
	}
	else
		return 1;
}

long Ftell(file *fp) {
	int result = (fp->var - fp->base);
	result = result > 0 ? result : -result;
	return result;
}

int Fclose(file *fp) {
	//write(fp->fd, fp->base, fp->count);
	int returnvalue;
	free(fp->base);
	returnvalue = close(fp->fd);
	free(fp);
	return returnvalue;
}

void fillbuff(file *fp) {
	int buffsize = checkbuff(fp);
	if(!buffsize)
		fp->base = (char *)realloc(fp->base, BUFFSIZE);
	if(!(fp->count))
		fp->base = fp->next;
	fp->count = read(fp->fd, fp->next, buffsize);
	fp->var = fp->next = fp->next + fp->count;
	*(fp->next) = '\0';
}

size_u checkbuff(file *fp) {
	if(fp->base == NULL)
		if((fp->base = fp->var = fp->next = (char *)malloc(BUFFSIZE)) == NULL)
			return BUFFSIZE;
	return (BUFFSIZE - fp->count);
}











