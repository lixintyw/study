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
	int fd = open("myfifo", O_RDONLY);
	char caMsg[64] = {'\0'};
	int ret = -1;
	while (1)
	{
		memset(caMsg, '\0', sizeof(caMsg));
		ret = read(fd, caMsg, 64);
		//若写端关闭了，read返回值为0
		if (0 == ret)
		{
			break;
		}
		printf("收到数据:\n");
		write(STDOUT_FILENO, caMsg, strlen(caMsg));
	}

	printf("Hello World\n");

	return 0;
}




