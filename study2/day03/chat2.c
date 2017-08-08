
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


int main(int argc,char *argv[])
{
	int pipefd[2] = {0};
	int ret = -1;

	ret = pipe(pipefd);
	if(-1 == ret)
	{
		perror("pipe");
		return -1;
	}

	pid_t pid = fork();
	if(pid > 0)
	{
		char ca_msg[64] = {'\0'};
		int sign = 0;
		while(1)
		{
			if(0 == sign)
			{
				printf("父进程输入:\n");
				memset(ca_msg,'\0',sizeof(ca_msg));
				read(STDIN_FIFENO,ca_msg,64);
				write(pipefd[1],ca_msg,strlen(ca_msg));
				if(0 == strcmp("exit\n",ca_msg))
				{
					break;
				}
				sign = 1;
			}
			else if(1 == sign)
			{
				memset(ca_msg,'\0',64);
				read(pipefd[0],ca_msg,64);
				printf("父进程显示数据:\n");
				write(STDOUT_FILENO,ca_msg,strlen(ca_msg));
				sign = 0;
			}
			sleep(1);
		}
	}
	else if(0 == pid)
	{
		char ca_msg[64] = {'\0'};
		int sign = 0;
		while(1)
		{
			memset(ca_msg,'\0',64);
			if(0 == sign)
			{
				read(pipefd[0],ca_msg,64);
				printf("子进程显示数据:\n");
				write(STDOUT_FILENO,ca_msg,strlen(ca_msg));
				sign = 1;
			}
			else if(1 == sign)
			{
				printf("子进程输入:\n");
				memset(ca_msg,'\0',sizeof(ca_msg));
				read(STDIN_FILENO,ca_msg,64);
				write(pipefd[1],ca_msg,strlen(ca_msg));
				if(0 == strcmp("exit\n",ca_msg))
				{
					break;
				}
				sign = 0;
			}
			sleep(1);
		}
	}
	else if(-1 == pid)
	{
		perror("fork");
		return -1;
	}
	printf("hello world");
	return 0;
}


