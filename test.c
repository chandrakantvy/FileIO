#include <stdio.h>
#include "file.h"

int main(int argc, char *argv[]) {
	file *fp;
	char ch[11];
	fp = Fopen(argv[1], "a+");
	if(fp == NULL) {
		printf("%d", fp->fd);
		printf("file couldn't open\n");	
		return 1;
	}	
	Fwrite("chandrakant", 11, 1, fp);
	Fread(&ch, 11, 1, fp);
	Fseek(fp, 2, SEEK_SET);
	Fread(&ch, 9, 1, fp);
	printf("%s", ch);
	return 0;
}
