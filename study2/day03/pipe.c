#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <errno.h>  //errno


//无名管道只能用于具有亲缘关系的进程间通信
//创建无名管道的进程结束后，无名管道也被释放

int main(int argc, char *argv[])
{
	int pipefd[2] = {0};
	int ret = -1;
	//创建管道，若成功则会将管道读写接口的文件描述符
	//放入数组中
	//写端文件描述符放入pipefd[1]中
	//读端文件描述符放入pipefd[0]中
	ret = pipe(pipefd);
	if (-1 == ret)
	{
		perror("pipe");
		return -1;
	}

	char *pMsg = "每一个人都是一道独特的风景";
	//将数据写入管道中
	ret = write(pipefd[1], pMsg, strlen(pMsg));
	if (-1 == ret)
	{
		perror("write");
		return -1;
	}

	char caMsg[64] = {'\0'};
	//从管道中读取数据
	ret = read(pipefd[0], caMsg, 64);
	if (ret > 0)
	{
		//将数据显示在标准输出
		write(STDOUT_FILENO, caMsg, ret);
		putchar('\n');
	}

	printf("Hello World\n");

	return 0;
}




