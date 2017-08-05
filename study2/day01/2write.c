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
	fd = open(argv[1]
			  , O_WRONLY | O_CREAT | O_APPEND
			  , 0664);
	if (-1 == fd)
	{
		printf("errno=%d, err:%s\n"
			   , errno, strerror(errno));
		return -1;
	}
	printf("打开文件成功\n");

	int ret = -1;	
	//fd:要操作的文件的文件描述符
	//pData:要写入的数据的地址
	//参数三：要写入的数据的大小
	printf("data:%s\n", argv[2]);
	printf("size = %d\n", strlen(argv[2]));
	ret = write(fd, argv[2], strlen(argv[2]));
	if (-1 == ret)
	{
		printf("errno=%d, err:%s\n"
			   , errno, strerror(errno));
		return -1;
	}
	printf("成功写入文件%d字节的数据\n", ret);

	close(fd);  //关闭文件

	return 0;
}
