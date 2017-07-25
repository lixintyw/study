#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
void signup();
void xunhuan(int *arr1,int *arr2);
void panduan(char a,int *arr1,int* arr2);
void shanghai(int *arr,int i);
void userming(int *arr,int i);
void comming(int *arr,int i);
void tui();
int main()
{	
	signup();
	int user[15]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	int com[15]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	srand((unsigned)time(NULL));
	xunhuan(com,user);
	return 0;
}
void signup()
{
	printf("请输入用户名\n");
	char name[10];
	scanf("%s",name);
	while(getchar()!='\n');
	char password[20];
	char pass[20]="123456789";
	printf("请输入密码：\n");
	scanf("%s",password);
	while(getchar()!='\n');
	strcmp(password,pass);
	while(0!=strcmp(password,pass)){
		printf("请再次输入密码\n");
		scanf("%s",password);
		while(getchar()!='\n');
		strcmp(password,pass);
	}
	
}
void xunhuan(int *arr1,int *arr2)
{		
	while(1)
	{
		system("clear");
		printf("1--->进攻\n2--->撤退\n请输入你的选择：");
		char choose;
		scanf("%c",&choose);
		while(getchar()!='\n');
		panduan(choose,arr1,arr2);
	}
}
void panduan(char a,int *arr1,int* arr2)
{		
	switch(a){	
		case '1':
			shanghai(arr1,3);
			comming(arr1,15);
			shanghai(arr2,3);
			userming(arr2,15);
			break;
		case '2':
			tui(arr2);
			break;
		default:
		printf("输入错误\n");
	}
		printf("按回车键继续");
		while(getchar()!='\n');
}
void shanghai(int *arr,int i)
{
	int j=0;
	int index=0;
	for(j=0;j<i;j++){
		index=rand()%15;
		arr[index]=0;
	}
	
}
void userming(int *arr,int i)
{
	int life=0;
	int j=0;
	for(j=0;j<i;j++){
		life=life+arr[j];
	}
	printf("玩家的生命值为：%d\n",life);
	if(life==0){
		printf("用户失败\n");
		exit(1);
	}
}
void comming(int *arr,int i)
{
	int j=0;
	int life=0;
	for(j=0;j<15;j++){
		life+=arr[j];
	}
	printf("电脑的生命值为：%d\n",life);
	if(life==0){
		printf("玩家获胜\n");
		exit(1);
	}
}
void tui(int *arr)
{
	int index=0;
	index=rand()%4;
	if(index==0){
		printf("撤退失败，电脑追击\n");
		shanghai(arr,3);
		userming(arr,15);
	}else{
		printf("撤退成功\n");
		exit(1);
	}

}
