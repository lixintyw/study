#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handle(int sig)
{
	if (SIGINT == sig)
	{
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
	}
	else if (SIGTSTP == sig)
	{
		//ctrl+z
		printf("this is SIGTSTP handle\n");
	}
}

int main(void)
{	
	struct sigaction act;
	act.sa_handler = handle;
	sigemptyset(&(act.sa_mask));
	sigaddset(&(act.sa_mask), SIGTSTP);

	//通过结构体同时设置某个信号的处理函数和需要屏蔽的信号集
	sigaction(SIGINT, &act, NULL);
	
	struct sigaction act2;
	act2.sa_handler = handle;
	sigaction(SIGTSTP, &act2, NULL);

	while (1)
	{
		printf("this is main while \n");
		sleep(1);
	}

	return 0;
}









