#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#if 0
服务员：客人到来信号 ctrl+c SIGINT
        点菜，发送信号给厨师做菜  SIGUSR1
		端菜，接收厨师发送的端菜信号  SIGUSR2
		客人吃完饭，买单信号  ctrl+z  SIGTSTP
		下班时间到了，通知服务员下班  ctrl+\ SIGQUIT
		通知厨师下班  SIGALRM
		处理 SIGCHLD

厨师：忽略SIGINT，SIGQUIT，SIGTSTP 
	  接收做菜信号 SIGUSR1
	  发送端菜信号 SIGUSR2
	  接收下班信号 SIGALRM

//可以用父进程模仿服务员，子进程模仿厨师
#endif

pid_t pid;

void handleServer(int sig)
{
	switch (sig)
	{
	case SIGINT:
		printf("有客人到来...\n");
		sleep(1);
		printf("服务员接待客人，点菜...\n");
		sleep(1);
		printf("服务员通知厨师做菜...\n");
		sleep(1);
		kill(pid, SIGUSR1);
		break;
	case SIGUSR2:
		printf("服务员给客人上菜...\n");
		break;
	case SIGTSTP:
		printf("客人要求买单，服务员收银...\n");
		sleep(1);
		printf("服务员说：欢迎下次光临...\n");
		sleep(1);
		break;
	case SIGQUIT:
		printf("下班时间到了，服务员通知厨师下班并收拾...\n");
		sleep(1);
		kill(pid, SIGALRM);
		break;
	case SIGCHLD:
		wait(NULL);
		printf("服务员关好门，下班...\n");
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}
void handleCook(int sig)
{
	if (SIGUSR1 == sig)
	{
		printf("厨师收到做菜菜单，开始做菜...\n");
		sleep(1);
		printf("厨师做好菜，通知服务员上菜...\n");
		sleep(1);
		kill(getppid(), SIGUSR2);
	}
	else if (SIGALRM == sig)
	{
		printf("厨师打扫厨房，下班...\n");
		sleep(1);
		exit(EXIT_SUCCESS);
	}
}

int main(void)
{
	pid  = fork();
	if (pid > 0)  //server
	{
		signal(SIGINT, handleServer);
		signal(SIGUSR2, handleServer);
		signal(SIGTSTP, handleServer);
		signal(SIGQUIT, handleServer);
		signal(SIGCHLD, handleServer);
	
		while (1)
		{
			pause();
		}
	}
	else if (0 == pid) //cook
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGUSR1, handleCook);
		signal(SIGALRM, handleCook);
		
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









