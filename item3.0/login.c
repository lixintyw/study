#include"login.h"
//void myGets(char * str, int size);
int  login(char * name , char * passwd)
{
	char newName[NAME_LEN] = {'\0'};
	char p[PWD_LEN] = {'\0'};
	char *newPasswd=p;
	int i=0;
	int j=0;
	while(i<3)
	{
		printf("请输入用户名密码，共三次机会\n");
		printf("请输入用户名:");
		myGets(newName,NAME_LEN);
		newPasswd=getpass("请输入密码：");
	
	
		if(strcmp(name,newName) == 0 && strcmp(passwd , newPasswd) == 0)
		{
		printf("欢迎进入\n");
		break;
		}
		else
		{
			printf("登录失败,请重新登录");
			printf("按下回车键继续");
			while(getchar() != '\n');
//		return 0;
		}
		i++;
	}
	if(i==3)	//进入print.c
	{
		printf("三次错误，自动退出\n");
		for(j=0;j<30;j++)
		{
//			system("clear");
			printf("\33[1A%d秒后可再次登录\33[K\n",30-j);
			sleep(1);
		}
		return 0;
	}
	else
		return 1;
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
