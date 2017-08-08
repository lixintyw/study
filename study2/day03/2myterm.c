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
	char caCommand[128] = {'\0'};
	char caRealCommand[16] = {'\0'};//ls
	char caArg[32] = {'\0'};//-a -l
	char caPro[64] = {'\0'};
	while (1)
	{
		memset(caCommand, '\0', 128);
		memset(caRealCommand, '\0', 16);
		memset(caArg, '\0', 32);
		memset(caPro, '\0', 64);


		printf("MYTERM $ \n");
//		scanf("%s", caCommand);	
		read(STDIN_FILENO,caCommand,128);
		p = strchr(caCommand,'\n');
		if(NULL != p)
		{
			*p  = '0';
		}
		else
		{
			while('\n' != getchar());
		}



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




