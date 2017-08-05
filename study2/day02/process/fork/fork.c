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
	unsigned int num = 0;
	char caMsg[32] = {'\0'};
	pid_t pid = -1;
	//产生一个子进程
	pid = fork();
	if (pid > 0) //parent
	{
		num = 2;
		strcpy(caMsg, "this is parent");
	}
	else if (0 == pid)  //child
	{
		num = 6;
		strcpy(caMsg, "this is child");
	}
	else if (-1 == pid)  //error
	{}

	for (; num >= 0; num--)
	{
		printf("msg:%s\n", caMsg);
		sleep(1);
	}

	printf("Hello World\n");

	return 0;
}




