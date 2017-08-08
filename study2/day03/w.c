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
	//若写打开一个有名管道
	//则会阻塞,直到有进程读打开该有名管道
	int fd = open("myfifo", O_WRONLY);
	char caMsg[64] = {'\0'};
	//若在运行过程中,读端被关闭
	//则系统会发送信号干掉本进程
	while (1)
	{
		memset(caMsg, '\0', sizeof(caMsg));
		printf("请输入数据:\n");
		read(STDIN_FILENO, caMsg, 64);
		write(fd, caMsg, strlen(caMsg));
	}

	printf("Hello World\n");

	return 0;
}




