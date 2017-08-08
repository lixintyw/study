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
	//ls -a -l ./tmp -la
	char caCommand[128] = {'\0'};
	char caRealCommand[16] = {'\0'};  //ls
	char caArg[32] = {'\0'};  // -a -l
	char caProject[64] = {'\0'};  // /home/sq
	char *p = NULL;
	char *q = NULL;
	char *m = NULL;
	while (1)
	{
		memset(caCommand, '\0', 128);
		memset(caRealCommand, '\0', 16);
		memset(caArg, '\0', 32);
		memset(caProject, '\0', 64);

		printf("MYTERM $ \n");
		//输入命令
		read(STDIN_FILENO, caCommand, 128);
		p = strchr(caCommand, '\n');
		if (NULL != p)
		{
			*p = '\0';
		}
		else
		{
			while ('\n' != getchar())
			{}
		}
		if (0 == strcmp("exit", caCommand))
		{
			break;
		}
		//提取要执行的命令
		p = strchr(caCommand, ' ');
		if (NULL != p)
		{
			strncpy(caRealCommand, caCommand
					, p-caCommand);
		}
		printf("11^^%s\n", caCommand);
		p = caCommand;
		//提取参数
		while (1)
		{
			p = strchr(p, '-');
			if (NULL != p)
			{
				q = strchr(p, ' ');
				if (NULL != q)
				{
					strncat(caArg, p, q-p);
					strcat(caArg, " ");
				}
				else if (NULL == q)
				{
					strcat(caArg, p);
					break;
				}
			}
			else
			{
				break;
			}
			p++;
		}
		p = strrchr(caArg, ' ');
		if (NULL != p)
		{
			q = p+1;
			if ('\0' == *q)
			{
				*p = '\0';
			}
		}	
		printf("22^^%s\n", caCommand);
		//提取作用对象
		p = strchr(caCommand, ' ');
		if (NULL != p)
		{
			while (1)
			{
				q = p+1;
				if (' ' == *p && '-' != *q)
				{
					m = strchr(q, ' ');
					if (NULL != m)
					{
						strncat(caProject, q, m-q);
						strcat(caProject, " ");
						p = m;
					}		
					else
					{
						strcat(caProject, q);
						break;
					}
				}
				else
				{
					p++;
				}
				if ('\0' == *p)
				{
					break;
				}
			}
		}

		printf("caCommand:%s, caRealCommand:%s, caArg:%s, caProject:%s\n"
			   , caCommand
			   , caRealCommand
			   , caArg, caProject);
#if 1
		pid = fork();
		if (pid > 0)
		{
			wait(NULL);
		}
		else if (0 == pid)
		{
//			execlp(caRealCommand, caRealCommand
//				   , caArg, caProject, NULL);
//			perror("execlp");
			//execlp("ls", "ls", "-a", "-l", "/home/sq", NULL);
			execlp("ls", "ls", "-la", "/home/sq", NULL);
				break;
		}
		else if (-1 == pid)
		{
			perror("fork");
			break;
		}
#endif
	}

	printf("Hello World\n");

	return 0;
}




