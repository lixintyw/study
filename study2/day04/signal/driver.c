#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <signal.h>

/*
 司机:接收拦车信号，停车  SIGINT(ctrl+c)
      发送开门信号让售票员开门 SIGUSR1
	  接收开车信号  SIGUSR2
 	
 售票员:接收开门信号开门 SIGUSR1
 		开门售票
		关门并发送开车信号给司机 SIGUSR2
 */

pid_t pid;

void driver(int sig)
{
	if (SIGINT == sig)
	{
		printf("有人拦车...\n");
		sleep(1);
		printf("司机停车...\n");
		sleep(1);
		kill(pid, SIGUSR1);
	}
	else if (SIGUSR2 == sig)
	{
		printf("司机开车...\n");
	}
}

void sall(int sig)
{
	if (SIGUSR1 == sig)
	{
		printf("售票员打开车门...\n");
		sleep(1);
		printf("乘客买票上车...\n");
		sleep(1);
		printf("售票员关好门...\n");
		sleep(1);
		kill(getppid(), SIGUSR2);
	}
}

int main(void)
{
	pid = fork();
	if (pid > 0)  //driver
	{
		signal(SIGINT, driver);
		signal(SIGUSR2, driver);
		while (1)
		{
			pause();
		}
	}
	else if (0 == pid)
	{
		signal(SIGUSR1, sall);
		signal(SIGINT, SIG_IGN);
		printf("售票员关好门\n");
		sleep(1);
		kill(getppid(), SIGUSR2);
		while (1)
		{
			pause();
		}	
	}
	else if (-1 == pid)
	{
		perror("fork");
		return -1;
	}


	return 0;
}
