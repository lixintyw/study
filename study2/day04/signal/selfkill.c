#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <signal.h>

int main(void)
{
	int i = 0;
	while (1)
	{
		printf("this is %dth while\n", i+1);
		sleep(1);
		i++;
		if (5 == i)
		{
			kill(getpid(), SIGKILL);
		}
	}

	return 0;
}
