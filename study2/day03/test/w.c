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
	int fd = open("myfifo", O_RDWR);
	char caMsg[64] = {'\0'};
	int sign = 0;
	while (1)
	{
		memset(caMsg, '\0', sizeof(caMsg));
		if (0 == sign)
		{
			printf("请输入数据:\n");
			read(STDIN_FILENO, caMsg, 64);
			write(fd, caMsg, strlen(caMsg));
			sign = 1;
		}
		else if (1 == sign)
		{
			read(fd, caMsg, 64);
			printf("获得数据:\n");
			write(STDOUT_FILENO, caMsg, strlen(caMsg));
			sign = 0;
		}
		sleep(1);
	}

	printf("Hello World\n");

	return 0;
}




