#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void menu();
void gameMenu();
void registe(char * name , char * passwd);
void myGets(char * str , int size);
void login(char * name , char * passwd);
void attack(int * arr);
int judge(int * arr , int flag);
int goHome();
int main()
{
	srand((unsigned)time(NULL));
	menu();
	return 0;
}

int goHome()
{
	int index = rand()%4;
	return index;  //返回值为0，表示撤退失败
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
		return 0;
	}else if(sum == 15 && flag == 1){
		printf("恭喜您，取得了战役的胜利\n");
		return 0;
	}
	return 1;
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


void login(char * name , char * passwd)
{
	char newName[20] = {'\0'};
	char newPasswd[20] = {'\0'};
	printf("请输入用户名:");
	myGets(newName,20);
	printf("请输入密码:");
	myGets(newPasswd,20);
	
	if(strcmp(name,newName) != 0 || strcmp(passwd , newPasswd) != 0){
		printf("登录失败,请重新登录\n");
		printf("按下回车键继续");
		while(getchar() != '\n');
	}else{
		//进入游戏
		gameMenu();
	}
}

void registe(char * name , char * passwd)
{
	char tmp1[20] = {'\0'};
	char tmp2[20] = {'\0'};
	printf("请输入用户名:");
	myGets(name,20);
	while(1)
	{
		printf("请输入密码:");
		myGets(tmp1,20);
		printf("请重新输入密码:");
		myGets(tmp2,20);
		if(strcmp(tmp1,tmp2) == 0)
		{
			strncpy(passwd,tmp1,strlen(tmp1));
			break;
		}else{
			printf("两次密码不一致，请重新输入\n");
		}
	}
}

void myGets(char * str, int size)
{
	int i = 0 ;
	for(i = 0 ; i < size -1 ; i++)
	{
		str[i] = getchar();
		if(str[i] == '\n')
		{
			break;
		}
	}
	str[i] = '\0';
	if(i == size -1){
		while(getchar() != '\n');
	}
}

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

void menu()
{
	char name[20] = {'\0'};
	char passwd[20] = {'\0'};
	while(1)
	{
		system("clear");
		printf("1-->注册\n"
				"2-->登录\n"
				"q-->退出\n"
				"请输入你的选择:");
		char ch = '\0';
		scanf("%c",&ch);
		while(getchar() != '\n');
		switch(ch)
		{
			case '1':
				registe(name,passwd);
				break;
			case '2':
				login(name,passwd);
				break;
			case 'q':
				//退出功能
				break;
			default:
				printf("输入错误，请重新输入\n");
	
		}
	}
}
