#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <signal.h>

int main(void)
{
	alarm(5);  //SIGALRM:结束程序
	alarm(2); //会将之前的闹钟取消

	while (1)
	{
		printf("aaaaaaa\n");
		sleep(1);
	}

	return 0;
}
