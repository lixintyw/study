#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
//线程锁  -->互斥量
pthread_mutex_t mutex;
//将多个语句合成一个原子操作
//原子操作不可分
//要么都执行
//要么都不执行

int i = 0;

void *run(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);
		i++;
		printf("thread i = %d\n", i);
		pthread_mutex_unlock(&mutex);
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
		pthread_mutex_lock(&mutex);
		i++;
		printf("main i = %d\n", i);
		pthread_mutex_unlock(&mutex);
	}

	//等待指定线程的结束
	pthread_join(thr, NULL);

	return 0;
}









