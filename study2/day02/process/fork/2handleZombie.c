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

//孤儿进程：父进程先于子进程结束
//则将该子进程称之为孤儿进程
//孤儿进程的收尸又祖宗进程接管

int main(int argc, char *argv[])
{
	pid_t pid = -1;
	//产生一个子进程
	pid = fork();
	if (pid > 0) //A
	{
		//阻塞等待子进程的结束
		//对子进程进行收尸处理
		wait(NULL);
		while (1)
		{
			printf("this is A:pid=%d\n", getpid());
			sleep(1);
		}
	}	
	else if (0 == pid)  //B
	{
		pid_t cpid = fork();
		if (cpid > 0)
		{
			//getpid()：获得进程本身的进程号
			printf("this is B:pid=%d\n", getpid());
			printf("B parent:pid=%d\n", getppid());
		}
		else if (0 == cpid)
		{
			int i = 0;
			while (1)
			{
				printf("c: %dth,pid=%d,parent=%d\n"
					   ,i+1, getpid(), getppid());
				sleep(1);
				if (++i == 5)
				{
					break;
				}
			}
		}
	}
	else if (-1 == pid)  //error
	{}


	printf("Hello World\n");

	return 0;
}




