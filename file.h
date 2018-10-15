typedef struct _file {
	int fd; //file descreptor
	int flags; // purpose of opening of file
	int count; //count the number of character left 
	char *base; //base address of the buffer
	char *next; // next charecter position
}file;
#define MAX_SIZE 20
#define PERM 0666  //permission of rd, wr, excute for owner, group & all other
enum _flags {
	READ = 01;
	WRITE = 02;
	UNBUF = 03;
	EOF = 04;
	ERR = 05;
};

extern file arrfile[MAX_FILE] = {
	{0, READ, 0, NULL, NULL}, {1, WRITE, 0, NULL, NULL}, {2, WRITE | UNBUF, 0, NULL, NULL}
}; // maximum files that can be opened in a program
file *Fopen(char *filepath, char *mode);
file Fclose(file *fp);
