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
	pid_t pid = -1;
	//产生一个子进程
	pid = fork();
	if (pid > 0) //parent
	{
		//阻塞等待子进程的结束
		//对子进程进行收尸处理
		int status;
		wait(&status);
		printf("retval = %d\n", WEXITSTATUS(status));
	}
	else if (0 == pid)  //child
	{
		int i = 0;
		while (1)
		{
			printf("this is child: %dth\n", i+1);
			sleep(1);
			if (++i == 5)
			{
				break;
			}
		}
		return 66;
	}
	else if (-1 == pid)  //error
	{}


	printf("Hello World\n");

	return 0;
}




