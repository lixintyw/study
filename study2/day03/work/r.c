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
	int fd = open("myfifo",O_RDWR);
	int fd2 = open("myfifo2",O_RDWR);
	char ca_msg[64] = {'\0'};
//	int sign = 1;
	pid_t pid = fork();
	if(pid > 0)
	{
		while(1)
		{
			memset(ca_msg,'\0',sizeof(ca_msg));
		//	if(1 == sign)
		//	{
				printf("输入数据:\n");
				//从标准输入获得数据
				read(STDIN_FILENO,ca_msg,64);
				//将数据写入管道
				write(fd2,ca_msg,strlen(ca_msg));
		//		sign = 0;
		//	}
	/*		else if(1 == sign)
			{
				read(fd,ca_msg,64);
				//若写端关闭了，read返回值为0
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
		//	if(0 == sign)
		//	{
				read(fd,ca_msg,64);
				//若写端关闭了，read返回值为0
				printf("收到数据:\n");
				write(STDOUT_FILENO,ca_msg,strlen(ca_msg));
		//		sign = 1;
		//	}
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
