#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

sigset_t set;

void handle(int sig)
{
	//ctrl+c
	if (SIGINT == sig)
	{
#if 0
		//若信号阻塞的操作是在信号的处理函数中进行的
		//则函数结束后，阻塞无效
		sigset_t set;
		//清空信号集合
		sigemptyset(&set);
		//添加SIGTSTP到集合中
		sigaddset(&set, SIGTSTP);
		//SIG_BLOCK:将信号集合中的信号阻塞
		//参数三：用来保存参数二中的信号之前的状态
		//NULL表示不保存之前的状态
		sigprocmask(SIG_BLOCK, &set, NULL);
#endif
		printf("$$$$$$$$$$$$$$$$\n");
		int i = 0;
		while (1)
		{
			printf("this is SIGINT handle\n");
			sleep(1);
			i++;
			if (5 == i)
			{
				break;
			}
		}
		//若有一个信号被阻塞但是多次发生
		//则解阻塞之后该信号只会被处理一次
		sigprocmask(SIG_UNBLOCK, &set, NULL);
	}
	else if (SIGTSTP == sig)
	{
		//ctrl+z
		printf("this is SIGTSTP handle\n");
	}
}

int main(void)
{	
//	sigset_t set;
	//清空信号集合
	sigemptyset(&set);
	//添加SIGTSTP到集合中
	sigaddset(&set, SIGTSTP);
	//SIG_BLOCK:将信号集合中的信号阻塞
	//参数三：用来保存参数二中的信号之前的状态
	//NULL表示不保存之前的状态
	sigprocmask(SIG_BLOCK, &set, NULL);
	
	signal(SIGINT, handle);	
	signal(SIGTSTP, handle);	

	while (1)
	{
		printf("this is main while \n");
		sleep(1);
	}

	return 0;
}









