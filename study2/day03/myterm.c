#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <errno.h>  //errno

int main(int argc, char *argv[])
{
	pid_t pid = -1;
	char caCommand[32] = {'\0'};
	while (1)
	{
		printf("MYTERM $ \n");
		memset(caCommand, '\0', 32);
		scanf("%s", caCommand);	
		if (0 == strcmp("exit", caCommand))
		{
			break;
		}
		pid = fork();
		if (pid > 0)
		{
			wait(NULL);
		}
		else if (0 == pid)
		{
			execlp(caCommand, caCommand, NULL);
			break;
		}
		else if (-1 == pid)
		{
			perror("fork");
			break;
		}
	}

	printf("Hello World\n");

	return 0;
}




