#include "file.h"

int open_file(const char *pathname,int flags)
{
	int fd = -1;
	fd = open(pathname,flags|O_CREAT,0664);
