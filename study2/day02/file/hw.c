#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>  //errno

int main(int argc, char *argv[])
{
	int fd = -1;
	fd = open(argv[1], O_RDONLY);
	if (-1 == fd)
	{
		perror("open");
		return -1;
	}
	//argv[1]: stu.info
	//caPathname: stu.info.tmp
	char caPathname[64] = {'\0'};
	strcpy(caPathname, argv[1]);
	strcat(caPathname, ".tmp");

	int newfd = -1;
	newfd = open(caPathname, O_WRONLY|O_CREAT, 0664);
	if (-1 == newfd)
	{
		perror("open new");
		return -1;
	}

	int pos = -1;
	printf("请输入插入数据的位置:\n");
	scanf("%d", &pos);
	
	off_t filesize = -1;
	//获得文件大小
	filesize = lseek(fd, 0, SEEK_END);
	if (pos > filesize)
	{
		pos = filesize;
	}
	else if (pos < 0)
	{
		pos = 0;
	}
	//重新将读写位置设置在文件首部
	lseek(fd, 0, SEEK_SET);

	char caBuf[4096] = {'\0'};
	int ret = -1;
	//将插入位置之前的数据拷贝到新的文件中
	while (pos)
	{
		memset(caBuf, '\0', 4096);
		if (pos > 4096)
		{
			ret = read(fd, caBuf, 4096);
		}
		else
		{
			ret = read(fd, caBuf, pos);
		}
		if (-1 == ret || 0 == ret)
		{
			break;
		}
		write(newfd, caBuf, ret);
		pos -= ret;
	}
	//将新增的数据放入新的文件中
	write(newfd, argv[2], strlen(argv[2]));

	//将插入位置之后的数据拷贝到新的文件中
	while (1)
	{
		memset(caBuf, '\0', sizeof(caBuf));
		ret = read(fd, caBuf, 4096);
		if (-1 == ret || 0 == ret)
		{
			break;
		}
		write(newfd, caBuf, ret);
	}

	close(fd);
	close(newfd);
	//将原来的文件删除
	remove(argv[1]);

	rename(caPathname, argv[1]);

	printf("Hello World\n");

	return 0;
}




