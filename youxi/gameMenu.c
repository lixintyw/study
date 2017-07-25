#include <stdio.h>
#include <stdlib.h>
#define NUM 100
#define LIVE 1
#define DEAD 0
int goHome();
int judge(int * arr,int flag);
void attack(int * arr);
void gameMenu()
{
	int user[15] = {0};
	int com[15] = {0};
	int flag = 1;
	while(flag)
	{
		system("clear");
		printf("1-->进攻\n"
				"2-->撤退\n"
				"请输入你的选择:");
		char ch = '\n';
		scanf("%c",&ch);
		while(getchar() != '\n');
		switch(ch)
		{
			case '1':
				attack(com);
				flag = judge(com,1);			
				if(flag)
				{
					attack(user);
					flag = judge(user,0);
				}
				break;
			case '2':
				if(!goHome()){
					printf("撤退失败~电脑追击\n");
					attack(user);
					flag = judge(user,0);
				}else{
					flag = 0;
				}
				break;
			default:
				printf("没有这个操作\n");
		}

		printf("按回车继续");
		while(getchar() != '\n');
	}
}
int goHome()
{
	int index = rand()%4;
	return index;  //返回值为0，表示撤退失败
}

void attack(int * arr)
{
	int i = 0;
	for(i = 0 ; i < 3 ; i++)
	{
		int index = rand()%15;
		arr[index] = 1;
	}
}



int judge(int * arr,int flag)
{
	int i = 0;
	int sum = 0;
	for(i = 0 ; i < 15 ; i++)
	{
		if(arr[i] == 1)
			sum++;
	}
	if(flag == 0)
		printf("用户牺牲了:%d个士兵\n",sum);
	else
		printf("电脑牺牲了:%d个士兵\n",sum);
	if(sum == 15 && flag == 0)
	{
		printf("电脑取得了胜利\n");
		return DEAD;
	}else if(sum == 15 && flag == 1){
		printf("恭喜您，取得了战役的胜利\n");
		return DEAD;
	}
	return LIVE;
}
