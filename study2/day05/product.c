#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

//信号量:用数字来表示资源的可用数量
//生产者和消费者问题
/*
 十个空盘子
 生产者往盘子中生产食物
     检查空盘子的数量，
	 若大于0则表示有空盘子可供生产,
	     生产了则空盘子量减一,有食物盘子量加一
	 若等于0则表示没有空盘子，则阻塞等待
 消费者消费盘子中的食物
	 检查有食物盘子的数量，若大于0则表示有食物消费
	     消费了则有食物盘子量减一，空盘子量加一
	 若等于0则表示没有有食物的盘子，则阻塞等待
 */

pthread_mutex_t proMutex;
pthread_mutex_t cusMutex;

#define DISH_NUM 10  //盘子的数量
#define CUS_NUM 15   //消费者的数量
#define PRO_NUM 5    //生产者的数量

sem_t emptysem; //空盘子信号量，表示空盘子资源数
sem_t fullsem;  //有食物盘子信号量，表示有食物资源数

//数组表示盘子
char g_caDish[DISH_NUM];

//生产者线程要执行的函数
//表示生产者将要往第几个盘子中生产食物
int g_iProNum = 0;
void *product(void *arg)
{
	int num = (int)arg;
	while (1)
	{
		//检查指定信号量的值
		//若值大于0，则表示有资源可用
		//将其值减一，往下执行
		//若值等于0，则表示没有资源可用
		//则阻塞等待，直到有资源可用
		sem_wait(&emptysem);
		
		pthread_mutex_lock(&proMutex);
		
		srand((unsigned int)time(NULL));
		g_caDish[g_iProNum] = rand() % 26 + 'A';
		printf("第%d个生产者往第%d个盘子中生产了%c食物\n", num+1, g_iProNum+1, g_caDish[g_iProNum]);
		g_iProNum = (g_iProNum+1)%DISH_NUM;
		
		pthread_mutex_unlock(&proMutex);
		
		//将fullsem的值加一
		//通知所有阻塞等待fullsem的线程
		sem_post(&fullsem);
		sleep(1);
	}
}

//消费者线程要执行的函数
int g_iCusNum = 0;
void *custom(void *arg)
{
	int num = (int)arg;
	while (1)
	{
		sem_wait(&fullsem);
		
		pthread_mutex_lock(&cusMutex);
		
		printf("第%d个消费者消费了第%d个盘子中的%c食物\n", num+1, g_iCusNum+1, g_caDish[g_iCusNum]);
		g_caDish[g_iCusNum] = '\0';
		g_iCusNum = (g_iCusNum+1)%DISH_NUM;
		
		pthread_mutex_unlock(&cusMutex);
		
		sem_post(&emptysem);
		sleep(1);
	}
}

int main(void)
{	
	memset(g_caDish, '\0', DISH_NUM);
	//初始化信号量
	//参数一:要初始化的信号量
	//参数二:设置该信号量用于进程间同步还是用于线程间同步
	//0：表示用于线程间
	//非0：表示用于进程间
	//参数三：信号量的整数值，代表资源的可用数
	sem_init(&emptysem, 0, 10);
	sem_init(&fullsem, 0, 0);

	pthread_t cus[CUS_NUM];
	int i = 0;
	//创建消费者线程
	for (; i < CUS_NUM; i++)
	{
		pthread_create(cus+i, NULL, custom
					   , (void*)i);
	}

	//创建生产者线程
	pthread_t pro[PRO_NUM];
	for (i = 0; i < PRO_NUM; i++)
	{
		pthread_create(pro+i, NULL, product
					   , (void *)i);
	}

	//等待线程结束
	for (i = 0; i < CUS_NUM; i++)
	{
		pthread_join(cus[i], NULL);
	}
	for (i = 0; i < PRO_NUM; i++)
	{
		pthread_join(pro[i], NULL);
	}

	return 0;
}









