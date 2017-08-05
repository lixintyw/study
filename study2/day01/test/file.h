#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>  //errno

int openFile(const char *pathname, int flags);
ssize_t readDataFromFile(int fd, void *buf, size_t count);
ssize_t writeDataToFile(int fd, void *buf, size_t count);

#endif
