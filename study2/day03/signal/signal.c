#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
//信号处理函数
void handle(int sig)
{
	if(SIGINT == sig)
	{
		printf("catched sigint\n");
	}


}
int main()

{
//ctrl+c:sigint
		//设置信号的处理动作
	signal(SIGINT,handle);
	while(1)
	{
		printf("this is main while\n");
		sleep(1);
	}

	return 0;
}
