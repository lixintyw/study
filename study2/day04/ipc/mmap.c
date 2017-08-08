#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include <errno.h>  //errno

#include <sys/mman.h> //mmap

int main(int argc, char *argv[])
{
	int fd = -1;
	//以读写的方式打开文件
	fd = open(argv[1], O_RDWR);
	if (-1 == fd)
	{
		perror("open");
		return -1;
	}

	void *addr = NULL;
	//1:NULL表示让系统自动映射到内存的合适位置
	//2:存储空间的大小
	addr = mmap(NULL, 1024, PROT_READ|PROT_WRITE
				, MAP_SHARED, fd, 0);
	//MAP_FAILED --> (void *)-1
	if (MAP_FAILED == addr)
	{
		perror("mmap");
		return -1;
	}	
	
	char *pData = "北京欢迎你";
	sprintf((char *)addr, "%s", pData);

	close(fd);
	munmap(addr, 1024);

	printf("Hello World\n");

	return 0;
}




