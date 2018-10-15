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
	EOF = 03;
	ERR = 04;
};

extern file arrfile[MAX_FILE]; // maximum files that can be opened
file *Fopen(char *filepath, char *mode);
file Fclose(file *fp);
