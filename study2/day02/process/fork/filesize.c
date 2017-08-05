#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>  //errno

void getStrFromSTDIN(void *buf, int count)
{
	printf("请输入数据:\n");
	//从标准输入获得count字节的数据放入buf中
	int ret = read(STDIN_FILENO, buf, count);

	//思考：输入的数据可能要大于count的大小
	//在这种情况下，需要将多余的数据读取掉
	//例如：我只需要读取10字节的数据
	//但是输入的时候输入了100字节
	//在读取了10字节的数据之后，还剩余90字节的数据
	//需要将剩余的数据读取掉，
	//否则会对后续的程序产生影响

	//通过在buf中查找是否包含有'\n'来判断是否将所有的输入的数据都读取到buf中
	char *p = strrchr(buf, '\n');
	//如果没有找到'\n',
	//则表示标准输入中还有数据没有读取
	//则使用循环将剩余的数据读取掉
	if (NULL == p)
	{
		((char*)buf)[count-1] = '\0';
		while ('\n' != getchar())
		{}
	}
	else//若找到了'\n',则表示将所有的输入的数据都读取到了buf中
	{
		//使用'\0'将'\n'替换掉
		*p = '\0';
	}
}

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDWR|O_CREAT, 0664);
	if (-1 == fd)
	{
		perror("open");
		return -1;
	}

	char caBuf[4096] = {'\0'};
	pid_t pid = -1;
	pid = fork();
	if (pid > 0) //parent
	{
		while (1)
		{
			memset(caBuf, '\0', sizeof(caBuf));
			//从标准输入中获得数据
			getStrFromSTDIN(caBuf, 4096);
//			scanf("%s", caBuf);
			//将数据写入文件
			write(fd, caBuf, strlen(caBuf));
			//如果输入的数据是exit
			//则结束循环，退出程序
			if (0 == strcmp("exit", caBuf))
			{
				break;
			}
		}
	}
	else if (0 == pid)  //child
	{
		off_t size = -1;
		off_t prev = -1;
		while (1)
		{
			//循环获得文件的大小
			size = lseek(fd, 0, SEEK_END);
			//若此次获得的文件大小和之前的不一样
			//则表示文件的内容发生了变化
			//则打印此次获得的文件的大小
			if (prev != size)
			{
				printf("文件大小：%d\n", size);
				prev = size;
			}
			sleep(1);
		}	
	}
	else if (-1 == pid)  //error
	{
	}

	printf("Hello World\n");

	return 0;
}




