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

int main(int argc, char *argv[])
{
	int shmid = -1;//编号，大小，操作
	shmid = shmget(0x1024,4096,IPC_CREAT|0664);
	if(-1 == shmid)
	{
		perror("shmget");
		return -1;
	}
	printf("shmid = %d\n",shmid);
	return 0;
}




