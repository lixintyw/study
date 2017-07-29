#include"login.h"
//void myGets(char * str, int size);
int  login(char * name , char * passwd)
{
	char newName[NAME_LEN] = {'\0'};
	char newPasswd[PWD_LEN] = {'\0'};
	printf("请输入用户名:");
	myGets(newName,NAME_LEN);
	printf("请输入密码:");
	myGets(newPasswd,PWD_LEN);
	
	if(strcmp(name,newName) != 0 || strcmp(passwd , newPasswd) != 0){
		printf("登录失败,请重新登录\n");
		printf("按下回车键继续");
		while(getchar() != '\n');
		return 0;
	}else{
		//进入print.c

			printf("欢迎进入\n");
			return 1;	
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
