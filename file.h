typedef struct _file {
	int fd; //file descreptor
	int flags; // mode of opening of file
}file;
#define MAX_SIZE 20
#define PERM 0666  //permission of rd, wr, excute for owner, group & all other
enum _flags {
	_READ = 01;
	_WRITE = 02;
	_EOF = 03;
	_ERR = 04;
};

extern file arrfile[MAX_FILE]; // maximum files that can be opened
file *Fopen(char *filepath, char *mode);
file Fclose(file *fp);
