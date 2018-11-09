#include <stdio.h>
#include "file.h"

int main(int argc, char *argv[]) {
	file *fp;
	int j;

	fp = Fopen(argv[1], "r");
	if(fp == NULL) {
		printf("file couldn't open\n");	
		return 1;
	}
	//int i = 200;
	//Fwrite(&i, sizeof(int), 1, fp);
	//Fseek(fp, 0, SEEK_SET);
	Fread(&j, 4, 1, fp);
	printf("%d", j);
	Fclose(fp);
	return 0;
}
