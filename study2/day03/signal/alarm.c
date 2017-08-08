#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>

int main()

{
	alarm(5);//设一个闹钟5，默认操作结束程序
	alarm(2);//将之前的取消
	while(1)
	{
		printf("aaaaaaaaaaaaaa\n");
		sleep(1);
		}


	return 0;
}
