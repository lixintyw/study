#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <signal.h>

void cook(int sig);
void server(int sig);
pid_t pid;
int main( int argc,char *argv[])
{
	pid = fork();
	if(pid > 0)
	{
		signal(SIGINT,server);
		signal(SIGUSR2,server);
		signal(SIGTSTP,server);
		signal(SIGQUIT,server);
		signal(SIGCHLD,server);
		while(1)
		{
			sleep(1);
				
		}
	}
	else if(0 == pid)
	{
		signal(SIGUSR1,cook);
		signal(SIGINT,SIG_IGN);
		signal(SIGQUIT,SIG_IGN);
		signal(SIGTSTP,SIG_IGN);
		signal(SIGALRM,cook);
		while(1)
		{
			pause();
		}
	}
	else if(-1 == pid)
	{
		perror("fork");
		return -1;
	}

	return 0;
}


void server(int sig)
{
	if(SIGINT == sig)
	{
		printf("有客到！！！\n");
		sleep(1);
		printf("客人已经点菜》》\n");
		sleep(1);
		kill(pid,SIGUSR1);
	}
	else if(SIGUSR2 == sig)
	{
		printf("服务员上菜\n");
		sleep(1);
	}
	else if(SIGTSTP == sig)
	{
		printf("服务员买单\n");
		sleep(1);
	}
	else if(SIGQUIT == sig)
	{
		printf("服务员下班\n");
		sleep(1);
		kill(pid,SIGALRM);
	}
	else if(SIGCHLD == sig)
	{
		wait(NULL);
		sleep(3);
		exit(1);
	}
}

void cook(int sig)
{
	if(SIGUSR1 == sig)
	{
		printf("厨师做菜\n");
		sleep(1);
		kill(getppid(),SIGUSR2);
	}
	else if(SIGALRM == sig)
	{
		printf("厨师下班\n");
//		kill(pid,SIGKILL);
		exit(1);
	//	kill(getppid(),SIGCHLD);
	}
}
