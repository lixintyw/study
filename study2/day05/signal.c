#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handle(int sig)
{
	//ctrl+c
	if (SIGINT == sig)
	{
		//若在处理A信号的过程中
		//该信号A再次发生(一次或者多次)
		//那么将会将该信号阻塞
		//知道本次信号处理完之后才会去处理
		//而且只处理一次


		//若在处理A信号的过程中
		//发生了B信号
		//那么会先去处理B信号
		//处理B信号之后再接着处理A信号
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
	signal(SIGINT, handle);	
	signal(SIGTSTP, handle);	

	while (1)
	{
		printf("this is main while \n");
		sleep(1);
	}

	return 0;
}









