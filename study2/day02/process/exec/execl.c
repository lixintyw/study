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
	//参数一:执行文件的路径
	//参数二:要执行的文件名
	//后续参数为文件执行时的参数
	//最后一个参数设置为NULL
	//execl("/usr/bin/gedit"
	//	  , "gedit", "./execl.c", NULL);
	//execl("/bin/ls"
	//	  , "ls", "-a", "-l", "/usr/", NULL);

	int i = 0;
	while (1)
	{
		printf("this is exec:pid=%d\n", getpid());
		i++;
		sleep(1);
		if (10 == i)
		{
			break;
		}
	}
	execl("/home/sq/tmp/test", "test", NULL);
	//execl("/tmp/test", "test", NULL);


	printf("Hello World\n");

	return 0;
}




