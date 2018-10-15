#include <stdio.h>
include "file.h"

int main(int argc, char *argv[]) {
	file *fp;
	fp = Fopen(argv[1], "W+");
	if(fp == NULL) {
		printf("file couldn't open\n");	
		return 1;
	}	
	return 0;
}
