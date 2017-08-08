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
	STU stu[5] = {{1001, "张三", 78}
			      , {1002, "李四", 78}
	              , {1003, "王五", 78}
	              , {1004, "赵六", 78}
	              , {1005, "小七", 78}};

	memcpy(addr, stu, sizeof(stu));

	shmdt(addr);

	printf("Hello World\n");

	return 0;
}




