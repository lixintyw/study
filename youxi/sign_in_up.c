#include <stdio.h>
#include <string.h>
#include "gameMenu.h"
#define NUM 100
void myGets(char * str , int size);
void registe(char * name , char * passwd);
void login(char * name , char * passwd)
{
	char newName[NUM] = {'\0'};
	char newPasswd[NUM] = {'\0'};
	printf("请输入用户名:");
	myGets(newName,NUM);
	printf("请输入密码:");
	myGets(newPasswd,NUM);
	
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
	char tmp1[NUM] = {'\0'};
	char tmp2[NUM] = {'\0'};
	printf("请输入用户名:");
	myGets(name,NUM);
	while(1)
	{
		printf("请输入密码:");
		myGets(tmp1,NUM);
		printf("请重新输入密码:");
		myGets(tmp2,NUM);
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

