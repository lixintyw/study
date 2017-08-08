#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	int i = 0;
	pid_t pid = atoi(argv[1]);
	while (1)
	{
		printf("this is %dth while\n", i+1);
		sleep(1);
		i++;
		if (5 == i)
		{
			printf("kill other process\n");
			kill(pid, SIGKILL);
		}
	}

	return 0;
}
