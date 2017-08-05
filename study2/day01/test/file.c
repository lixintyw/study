#include "file.h"

int openFile(const char *pathname, int flags)
{	
	int fd = -1;
	fd = open(pathname, flags|O_CREAT, 0664);
	if (-1 == fd)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return fd;
}

ssize_t readDataFromFile(int fd, void *buf, size_t count)
{
	ssize_t iReaded = 0;
	if (NULL != buf)
	{	
		int ret = -1;
		while (1)
		{
			if (count > 4096)
			{
				ret = read(fd, buf, 4096);
			}
			else
			{
				ret = read(fd, buf, count);
			}
			if (-1 == ret)
			{
				perror("read");
				break;
			}
			else if (0 == ret)
			{
				break;
			}
			iReaded += ret;
			count -= ret;
			buf = (char *)buf + ret;
		}
	}
	return iReaded;
}

ssize_t writeDataToFile(int fd, void *buf, size_t count)
{
	ssize_t iWrited = 0;
	if (NULL != buf)
	{
		int ret = 0;
		while (count)
		{
			if (count > 4096)
			{
				ret = write(fd, buf, 4096);
			}
			else
			{
				ret = write(fd, buf, count);
			}
			if (-1 == ret || 0 == ret)
			{
				break;
			}
			iWrited += ret;
			count -= ret;
			buf = (char *)buf + ret;
		}
	}

	return iWrited;
}
