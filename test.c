#include <stdio.h>
#include "file.h"

int main(int argc, char *argv[]) {
	file *fp;
	int i = 12345;
	fp = Fopen(argv[1], "a+");
	if(fp == NULL) {
		printf("%d", fp->fd);
		printf("file couldn't open\n");	
		return 1;
	}	
	Fwrite("chandrakant", 11, 1, fp);
	printf("%s", fp->base);
	return 0;
}
