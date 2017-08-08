#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/wait.h>

#include<errno.h>//errno

int main(int argc,char *argv[])
{
	//若写打开一个有名管道
	//则会阻塞，直到有进程读打开该有名管道
	int fd = open("myfifo",O_RDWR);
	int fd2 = open("myfifo2",O_RDWR);
	char ca_msg[64] = {'\0'};
	//若在运行过程中，读端被关闭
	//则系统会发送信号干掉本进程
	pid_t pid = fork();
//	int sign = 0;
	if(pid > 0)
	{
		while(1)
		{
			memset(ca_msg,'\0',sizeof(ca_msg));
	//		if(0 == sign)
	//		{
				printf("请输入数据:\n");
				read(STDIN_FILENO,ca_msg,64);
				write(fd,ca_msg,strlen(ca_msg));
	//			sign = 1;
	//		}
	/*		else if(1 == sign)
			{
				read(fd,ca_msg,64);
				printf("收到数据:\n");
				write(STDOUT_FILENO,ca_msg,strlen(ca_msg));
				sign = 0;
				
			}*/
		}
	}
	else if(0 == pid)
	{
		while(1)
		{
	//		if(1 == sign)
	//		{
				read(fd2,ca_msg,64);
				printf("收到数据:\n");
				write(STDOUT_FILENO,ca_msg,strlen(ca_msg));
	//			sign = 0;
	//		}
		}
	}

	else if(-1 == pid)
	{
		perror("fork\n");
		return -1;
	}

	sleep(1);

	printf("Hello world\n");
	
	return 0;
}
