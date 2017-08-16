#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
/*semget*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

pthread_mutex_t pmutex;
pthread_mutex_t gmutex;

//联合体
//是一种自定义的数据类型
//
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short  *array;
	struct seminfo  *__buf;
};

#define NUM 5
//用来保存信号量集合的标识符
int semid = -1;
//获得筷子
void getChopsticks(int num)
{
	int left = num;
	int right = (num+1)%NUM;

	//成员一:操作集合中第几个信号量
	//成员二:-1表示获得资源，1表示释放资源
	//成员三:0表示若资源不满足则阻塞等待直到满足为止
	struct sembuf sem[2] = {{left, -1, 0}
			                , {right, -1, 0}};
	//通过结构体指定的操作来操作集合中的信号量
	semop(semid, sem, 2);
}
//放下筷子
void putChopsticks(int num)
{
	int left = num;
	int right = (num+1)%NUM;

	//成员一:操作集合中第几个信号量
	//成员二:-1表示获得资源，1表示释放资源
	//成员三:0表示若资源不满足则阻塞等待直到满足为止
	struct sembuf sem[2] = {{left, 1, 0}
			                , {right, 1, 0}};
	//通过结构体指定的操作来操作集合中的信号量
	semop(semid, sem, 2);
}

void *run(void *arg)
{
	int num = (int)arg;
	while (1)
	{
		printf("第%d个哲学家正在思考...\n", num+1);
		sleep(1);
		//获得筷子吃饭
		pthread_mutex_lock(&gmutex);
		getChopsticks(num);
		printf("第%d个哲学家获得筷子吃饭...\n", num+1);
		pthread_mutex_unlock(&gmutex);
		sleep(1);

		pthread_mutex_lock(&pmutex);
	
		putChopsticks(num);
		printf("第%d个哲学家放下筷子...\n", num+1);
	
		pthread_mutex_unlock(&pmutex);
		
		sleep(1);
	}
}

int main(void)
{
	int i = 0;
	//创建信号量集合
	//参数一：使用一个十六进制的整数作为该集合的名字
	//        名字可以重复
	//参数二: 设置该集合中信号量的个数
	//IPC_CREAT|0664:创建集合并指定操作权限
	//成功返回该集合的标识符，
	//通过标识符来唯一确定集合
	semid = semget(0x1024, NUM, IPC_CREAT|0664);
	union semun sem;
	sem.val = 1;
	for (i = 0; i < NUM; i++)
	{
		//设置集合中信号量的值
		//参数一：集合标识符
		//参数二：集合中第几个信号量
		//参数三：对集合的操作命令
		//    SETVAL:对信号量赋值
		//参数四：根据命令传入不定个数的数据
		semctl(semid, i, SETVAL, sem);
	}

	pthread_t thr[NUM];
	//创建五个哲学家线程
	for (i=0; i<NUM; i++)
	{
		pthread_create(thr+i, NULL, run, (void*)i);
	}
	//等待线程结束
	for (i=0; i<NUM; i++)
	{
		pthread_join(thr[i], NULL);
	}

	return 0;
}









