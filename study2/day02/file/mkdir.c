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
	int ret = -1;
	//参数一：路径
	//参数儿：权限
	//创建成功返回0，失败返回-1
	ret = mkdir(argv[1], 0777);
	if (-1 == ret)
	{
		perror("mkdir");
		return -1;
	}
	printf("创建%s成功\n", argv[1]);

	printf("Hello World\n");

	return 0;
}




