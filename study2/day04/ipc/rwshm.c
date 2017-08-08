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
	void *addr = NULL;
	//参数二：NULL让系统自动将共享内存关联到进程合适位置
	//参数三：0表示读写
	//SHM_RDONLY:表示只读
	//没有只读
	//成功：返回值为共享内存的地址
	//失败：返回值为(void *)-1
	addr = shmat(shmid, NULL, 0);
	if ((void *)-1 == addr)
	{
		perror("shmat");
		return -1;
	}
	
	char *pMsg = "欢迎来到上海";

	//将数据拷贝到共享内存中
	//strcpy((char *)addr, pMsg);
	//sprintf((char*)addr, "%s", pMsg);
	//memcpy(addr, pMsg, strlen(pMsg));
	char *p = (char *)addr;
	while ('\0' != *pMsg)
	{
		*p = *pMsg;
		p++;
		pMsg++;
	}
	*p = '\0';

	//将数据从共享内存中拷贝出来
	char caMsg[64] = {'\0'};
//	strcpy(caMsg, (char*)addr);
//	sscanf((char*)addr, "%s", caMsg);
	memcpy(caMsg, addr, 64);
	printf("msg:%s\n", caMsg);

	//取消关联
	shmdt(addr);

	printf("Hello World\n");

	return 0;
}




