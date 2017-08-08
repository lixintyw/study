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

int main(int argc, char *argv[])
{
	int pipefd[2] = {0};
	int ret = -1;
	//创建管道
	ret = pipe(pipefd);
	if (-1 == ret)
	{
		perror("pipe");
		return -1;
	}
	//创建子进程
	//通过管道实现父子进程间的通信
	pid_t pid = fork();
	if (pid > 0) //parent
	{
		char caMsg[64] = {'\0'};
		int sign = 0;
		while (1)
		{
			if (0 == sign)
			{
				printf("父进程输入:\n");
				memset(caMsg, '\0', sizeof(caMsg));
				//从标准输入获得数据
				read(STDIN_FILENO, caMsg, 64);
				//将数据写入管道
				write(pipefd[1], caMsg, strlen(caMsg));
				if (0 == strcmp("exit\n", caMsg))
				{
					break;
				}
				sign = 1;
			}
			else if (1 == sign)
			{
				memset(caMsg, '\0', 64);
				//从管道中读取数据
				//若管道中没有数据，则阻塞等待数据
				read(pipefd[0], caMsg, 64);
				//将数据显示
				printf("父进程显示数据:\n");
				write(STDOUT_FILENO, caMsg, strlen(caMsg));
			    sign = 0;
			}
			sleep(1);
		}
	}
	else if (0 == pid) //child
	{
		char caMsg[64] = {'\0'};
		int sign = 0;
		while (1)
		{
			memset(caMsg, '\0', 64);
			if (0 == sign)
			{
				//从管道中读取数据
				//若管道中没有数据，则阻塞等待数据
				read(pipefd[0], caMsg, 64);
				//将数据显示
				printf("子进程显示数据:\n");
				write(STDOUT_FILENO, caMsg, strlen(caMsg));
				sign = 1;
			}
			else if (1 == sign)
			{
				printf("子进程输入:\n");
				memset(caMsg, '\0', sizeof(caMsg));
				//从标准输入获得数据
				read(STDIN_FILENO, caMsg, 64);
				//将数据写入管道
				write(pipefd[1], caMsg, strlen(caMsg));
				if (0 == strcmp("exit\n", caMsg))
				{
					break;
				}
				sign = 0;
			}
			sleep(1);
		}
	}
	else if (-1 == pid)  //error
	{
		perror("fork");
		return -1;
	}

	printf("Hello World\n");

	return 0;
}




