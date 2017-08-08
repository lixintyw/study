
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

int main(int argc,char *argv[])
{
	int pipefd[2] = {0};
	int ret = -1;
	//与管道有关 的笔记

	//无名管道只能用于具有类似域父子进程之间的关系
	//当创建无名管道的进程结束后，无名管道也被释放
	//创建管道，若成功则会将管道读写借口的
