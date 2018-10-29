typedef struct _file {
	int fd; //file descreptor
	int flag; // purpose of opening of file
	int count; //count the number of character left 
	char *base; //base address of the buffer
	char *next; // next charecter position
}file;

enum _flags {
	READ = 01,
	WRITE = 32,
	UNBUF = 04,
	_EOF = 10,
	_ERR = 20
};

#define MAX_FILE 20
#define PERM 0666  //permission of read, write for owner, group & all other
#define BUFFSIZE 1024

/*
#if !defined(HDR)
#define HDR
	file arrfile[MAX_FILE] = {
		{0, READ, 0, NULL, NULL}, {1, WRITE, 0, NULL, NULL}, {2, WRITE | UNBUF, 0, NULL, NULL}
	}; // maximum files that can be opened in a program
#endif */

typedef unsigned int size_u; 

file *Fopen(char *filepath, char *mode);
size_u Fwrite(void *buf, size_u size, size_u nmemb, file *fp);
void fillbuff(file *fp);
file Fclose(file *fp);
