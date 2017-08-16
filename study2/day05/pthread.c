#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
//创建线程，即创建一个并发执行的流程
//该线程从属于进程，不和进程分离
//进程和线程间共享所有资源

//进程结束，所有的线程都将结束
//线程结束对进程影响不大

void *run(void *arg)
{
	int num = (int)arg;
	while (1)
	{
		printf("this is thread run:%d\n", num);
		sleep(1);
	}	
}

int main(void)
{	
	pthread_t thr;
	int ret = -1;
	//创建线程
	//参数一：设置线程的标识
	//参数二:设置线程的属性(优先级等)
	//参数三:设置线程要执行的代码
	//参数四:设置要传给线程的参数
	//若创建成功，则执行run函数
	//ret = pthread_create(&thr, NULL, run, NULL);
	ret = pthread_create(&thr, NULL, run
				         , (void *)888);
	if (0 != ret)
	{
		perror("pthread_create");
		return -1;
	}

	while (1)
	{
		printf("this is main while\n");
		sleep(1);
	}

	//等待指定线程的结束
	pthread_join(thr, NULL);

	return 0;
}









