#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define NUM 20
#define ARMY 15
void mainMenu();
void myGets(char *str,int size);
int judge(int *arr,int flag);
void registe(char *name,char*passwd);
void gameMenu();
int withdraw();
void attack(int *arr);
void login(char *name,char *passwd);
int main()
{
	
	srand((unsigned)time(NULL));
	mainMenu();
	return 0;
}
void mainMenu()
{	
	char name[NUM]={'\0'};
	char passwd[NUM]={'\0'};
	while(1)
	{	
		system("clear");
		printf("请选择要输入的选项：\n");
		printf("1-->注册\t2-->登录\tq-->离开\n");
		char choose='\0';
		scanf("%c",&choose);
		while(getchar()!='\n');
		switch(choose)
		{
			case '1':
			{	
				printf("请开始注册\n");
				registe(name,passwd);
				break;
			}
			case '2':
			{
				printf("请开始登录\n");
				login(name,passwd);
				break;
			}
			case 'q':
			{
				printf("正在离开\n");
				exit(1);
				break;
			}
			default:
			{		
				printf("没有此类操作\n");
				printf("按回车键继续\n");
				while(getchar()!='\n');
				break;
			}
		}
	}
}
void registe(char *name,char *passwd)
{
	char temp1[NUM]={'\0'};
	char temp2[NUM]={'\0'};
	printf("请输入用户名：\n");
	myGets(name,20);
	while(1)
	{
		printf("请输入密码\n");
		myGets(temp1,NUM);
		printf("请再次输入密码\n");
		myGets(temp2,20);
		if(strcmp(temp1,temp2)!=0)
		{
			printf("两次密码不一样，请重新输入\n");
		}else{
			strncpy(passwd,temp1,strlen(temp1));
				break;
		}
	}	
}
void login(char *name,char *passwd)
{
	char newName[NUM]={'\0'};
	char newPasswd[NUM]={'\0'};
	printf("请输入用户名\n");
	myGets(newName,NUM);
	printf("请输入密码\n");
	myGets(newPasswd,NUM);
	if(strcmp(newName,name)!=0||strcmp(newPasswd,passwd)!=0)
	{	
			printf("用户名或密码输入错误，请重新输入\n");
			printf("按下回车键继续\n");
			while(getchar()!='\n');
	}else{
		gameMenu();
	}
}
void myGets(char *str,int size)
{
	int i=0;
	for(i=0;i<size-1;i++)
	{
		str[i]=getchar();
		if(str[i]=='\n')
		{
			break;
		}
	}
	str[i]='\0';
	//把第size-1位赋值，作为结束
	if(i==size-1){
		while(getchar()!='\n');
	}//消除后面多余的字符
}
void gameMenu()
{
	int user[ARMY]={0};
	int com[ARMY]={0};
	int flag=1;
	while(flag)
	{
		system("clear");
		printf("请输入游戏方式\n");
		printf("1->进攻\n2->撤退\n");
		char ch='\0';
		scanf("%c",&ch);
		while(getchar()!='\n');
		switch (ch)
		{
			case '1':
				attack(com);		//玩家进攻电脑

				flag=judge(com,0);	//判定电脑血量
				if(flag)
				{
					attack(user);	//判胜负
					flag=judge(user,1);	//电脑进攻玩家
				}	//判定玩家血量
			break;
			case '2':
				if (!withdraw())
				{
					printf("撤退失败电脑追击\n");
					attack(user);
					flag=judge(user,1);
				}else{
					printf("撤退成功，逃之夭夭，不要脸\n");
					flag=0;
				}
				break;
			default:
				printf("没有这样的操作 \n");

		}
		
		
		printf("按回车继续\n");
		while(getchar() != '\n');
	}
}


void attack(int *arr)
{
		//随机死亡三人
		//映入数组袁术
		//判定谁的进攻回合
	int i=0;
	for(i=0;i<3;i++)
	{
		int index=rand()%15;
		arr[index]=1;
	}
}
int judge(int *arr,int flag)
{
	int sum=0;
	int i=0;
	for(i=0;i<ARMY;i++)
	{
		sum=sum+arr[i];
	}
	if(flag==0)
	{
		printf("电脑牺牲了%d个士兵\n",sum);
	}else
	{
		printf("玩家牺牲了%d个士兵\n",sum);
	}
	if((sum==ARMY)&&(flag==0))//玩家进攻电脑
	{
		printf("玩家获胜\n");
		return 0;
	}else if((sum==ARMY)&&(flag==1))
	{	
			printf("电脑获胜\n");
			return 0;
	}
	return 1;
}
int withdraw()
{
	int index=rand()%4;
	return index;
}
























