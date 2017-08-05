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

	char caBuf[4096] = {'\0'};
	int ret = -1;
	//fd:要操作的文件
	//caBuf:数据存放的地址
	//参数三:预期要读取多少数据
	//返回值：实际读到的数据的字节大小
	ret = read(fd, caBuf, sizeof(caBuf));//strlen(caBuf)
	if (-1 == ret)
	{
		perror("read");
		return -1;
	}
	//0==ret:读到文件末尾或者空文件-->无数据可读
	else if (0 == ret)
	{
		return 0;
	}
	printf("读到%d字节的数据:%s\n", ret, caBuf);

	close(fd);  //关闭文件

	return 0;
}
