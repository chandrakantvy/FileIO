#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include "file.h"
file *Fopen(char const *filepath, char const *mode) {
	file *fp = (file*)malloc(sizeof(file));
	
	if(!strcmp("w", mode)) 
		fp->mode = O_WRONLY | O_CREAT | O_TRUNC;
	else if(!strcmp("r", mode)) 
		fp->mode = O_RDONLY;
	else if(!strcmp("a", mode)) 
		fp->mode = O_APPEND | O_CREAT;
	else if(!strcmp("w+", mode))
		fp->mode = O_RDWR | O_CREAT | O_TRUNC;
	else if(!strcmp("r+", mode)) 
		fp->mode = O_RDWR;
	else if(!strcmp("a+", mode))
		fp->mode = O_APPEND | O_CREAT;
	else
		fp->err = EINVAL;
	
	fp->flags = open(filepath, fp->mode);
	if(fp->flags){
		free(fp);
		fp = NULL;	
	}	
	return fp;
}


