#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	printf("请选择你要出的选项\n1-->石头\t2-->剪刀\t3-->布\n");

	int a,b,c,select;
	scanf("%d",&select);
	srand((unsigned)time(NULL));
	a=rand();
	b=a%3+1;
	if(1==b){
		printf("系统随机出的是石头\n");
	}else if(2==b){
		printf("系统随机出的是剪刀\n");
	}else{
		printf("系统随机出的是布\n");
	} 
	if(1==select){
		printf("你出的是石头\n");
	}else if(2==select){
		printf("你出的是剪刀\n");
	}else{
		printf("你出的是布\n");
	}
	if(select==b){
		printf("打和\n");
	}else if(((select==1)&&(b==2))||((select==2)&&(b==3))||((select==3)&&(b=1))){
		printf("恭喜你，赢了！\n");
	}else{
		printf("对不起，你输了！\n");
	}
	return 0;
}

