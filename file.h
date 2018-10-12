typedef struct file {
	int flags;
	int mode;
	int err;
}file;
file *Fopen(char const *filepath, char const *mode);

