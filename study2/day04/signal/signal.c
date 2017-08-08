#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <signal.h>
//SIGKILL和SIGSTOP不能使用自己的处理方式来处理
//信号的处理函数
void handle(int sig)
{
	if (SIGINT == sig)
	{
		printf("catched sigint\n");
	}
}

int main(void)
{
	//ctrl+c: SIGINT
	//设置信号的处理动作
	signal(SIGINT, handle);
	while (1)
	{
		printf("this is main while\n");
		sleep(1);
	}

	return 0;
}
