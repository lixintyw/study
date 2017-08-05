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
	//若以以下方式打开文件，
	//若文件不存在不会自动创建文件
	
	//参数一：要打开的文件
	//参数二：
	//    O_RDONLY-->表示以只读的方式打开文件
	//    O_WRONLY-->表示以只写的方式打开文件
	//    O_RDWR-->表示以读写的方式打开文件
	fd = open(argv[1], O_RDONLY);
	//fd = open(argv[1], O_WRONLY);
	//fd = open(argv[1], O_RDWR);
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
