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
	void *addr = NULL;
	addr = shmat(shmid,NULL,0);
	//参数二ＮＵＬＬ让系统自动将共享内存关联到进程合适位置
	//参数三　０　表示读写
	//ＳＨＭ——RDONLY，表示只写
	//没有制度
	//成功返回共享空间内存地址
	//失败void× -1；
	if((void *)-1 == addr)
	{
		perror("shmat");
		return -1;
	}
	char *p_msg = "welcome";
	strcpy((char *)addr,p_msg);

	char ca_msg[64] = {'\0'};
	strcpy(ca_msg,(char*)addr);
	printf("msg :%s\n",ca_msg);

	shmdt(addr);
	return 0;
}




