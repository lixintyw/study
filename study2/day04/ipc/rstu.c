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

#include "student.h"

int main(int argc, char *argv[])
{
	int shmid = -1;
	//创建一块共享内存，程序结束后仍然存在
	//电脑关机被释放
	shmid = shmget(0x1024, 4096, IPC_CREAT|0664);
	if (-1 == shmid)
	{
		perror("shmget");
		return -1;
	}
	printf("shmid = %d\n", shmid);

	void *addr = shmat(shmid, NULL, 0);
	
	STU tmp;
	//获得第一个学生的信息
	memcpy(&tmp, addr, sizeof(STU));
	showStuInfo(&tmp);

	//获得第4个学生的信息
	addr = (STU *)addr + 3;
	memcpy(&tmp, addr, sizeof(STU));
	showStuInfo(&tmp);

	//获得第2个学生的信息
	addr = (STU *)addr - 2;
	memcpy(&tmp, addr, sizeof(STU));
	showStuInfo(&tmp);

	shmdt(addr);

	printf("Hello World\n");

	return 0;
}




