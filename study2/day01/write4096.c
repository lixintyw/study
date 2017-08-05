#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>  //errno

ssize_t writeDataToFile(int fd, void *buf
				        , size_t count)
{
	ssize_t iWrited = 0;
	if (NULL != buf)
	{
		int ret = -1;
		while (count)
		{
			if (count > 4096)
			{
				ret = write(fd, (char*)buf+iWrited
						    , 4096);
			}
			else
			{
				ret = write(fd, (char*)buf+iWrited
							, count);
			}
			if (-1 == ret || 0 == ret)
			{
				break;
			}
			iWrited += ret;
			count -= ret;
	//		buf = (char *)buf+ret;
		}
	}
	return iWrited;
}

int main(int argc, char *argv[])
{
	int fd = -1;
	//O_CREAT:若文件不存在，则以指定的权限创建文件
	fd = open(argv[1], O_WRONLY | O_CREAT, 0664);
	if (-1 == fd)
	{
		printf("errno=%d, err:%s\n"
			   , errno, strerror(errno));
		return -1;
	}
	printf("打开文件成功\n");

	double buf[99999];
	writeDataToFile(fd, buf, sizeof(buf));

	close(fd);  //关闭文件

	return 0;
}
