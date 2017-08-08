#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <errno.h>  //errno
#include<sys/mman.h>
int main(int argc, char *argv[])
{
	int fd = -1;
	fd = open(argv[1],O_RDWR);
	if(-1 == fd)
	{
		perror("open");
		return -1;
	}

	
	void *addr = NULL;
	//表示系统自动映射到内存的合适位置
	//存储空间的大小
	addr = mmap(NULL,1024, PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(MAP_FAILED == addr)
	{
		perror("mmap");
		return -1;
	}
	char *p_data = "bjhyn";
	sprintf((char *)addr,"%s",p_data);
	close(fd);
	munmap(addr,1024);
		return 0;
}




