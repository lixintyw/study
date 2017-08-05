#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>  //errno

int main(int argc, char *argv[])
{
	int fd = -1;
	//O_CREAT:若文件不存在，则以指定的权限创建文件
	fd = open(argv[1], O_RDONLY | O_CREAT, 0664);
	if (-1 == fd)
	{
		printf("errno=%d, err:%s\n"
			   , errno, strerror(errno));
		return -1;
	}
	printf("打开文件成功\n");
	close(fd);  //关闭文件

	return 0;
}
