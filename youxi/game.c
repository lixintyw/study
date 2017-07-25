#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
	int user[15]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	int com[15]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	srand((unsigned)time(NULL));
	while(1)
	{
		system("clear");
		printf("1--->进攻\n2--->撤退\n请输入你的选择：");
		char choose;
		int i=0;
		int index=0;
		int life=0;
		scanf("%c",&choose);
		while(getchar()!='\n');
		switch(choose)
		{	
			case '1':
				for(i=0;i<3;i++)
				{
					index=rand()%15;
					com[index]=0;
					}
				for(i=0;i<15;i++)
				{
					life+=com[i];
				}
				printf("电脑的生命值为：%d\n",life);
				if(life==0)
				{
					printf("玩家获胜\n");
					exit(1);
				}
				for(i=0;i<3;i++)
				{
					index=rand()%15;
					user[index]=0;
				}
				life=0;
				for(i=0;i<15;i++)
				{
					life+=user[i];
				}
				printf("用户的生命为：%d\n",life);
				if(life==0)
				{
					printf("用户失败\n");
					exit(1);
				}
				break;
		case '2':
			index=rand()%4;
			if(index==0)
			{
				printf("撤退失败，电脑追击\n");
				for(i=0;i<3;i++)
			{	index=rand()%15;
					user[index]=0;

			}
				life=0;
				for(i=0;i<15;i++)
			{
				life+=user[i];
			}
			printf("用户的生命值为：%d\n",life);
			if(life==0)
			{
				printf("用户失败\n");
				exit(1);
			}}
		else{
				printf("撤退成功\n");
				exit(1);
		}break;
		default:
			printf("输入错误\n");
		}
		printf("按回车键继续");
		while(getchar()!='\n');
	}
	return 0;
}
