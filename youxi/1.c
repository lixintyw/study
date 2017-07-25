#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
	//界面输出
	//选择	
	//判定双方的对战模式
	printf("请输入你选择的对战模式\n");
	printf("1为进攻，2为撤退\n");
	scanf("%d",&choose);
	while(getchar()!='\n');
	srand=time(NULL);
	result=rand();
	result1=rand();
	if((result%2)==1){
		printf("电脑选择进攻\n");
	}else if{
		printf("电脑选择撤退\n");
		if(result%8==0){
		printf("电脑撤退失败\n");
		}else{
		printf("电脑撤退成功\n");
	}

//进攻
//10个人，每人一点血


	for(i=0;i<10;i++){
	
		user[i]=1;
		computer[i]=1;
	}//全部赋值为一
    srand=time(NULL);
	a=rand();//suiji 
//是否战争继续的条件
	for(i=0;i<10;i++){
		sum=sum+computer[i];
		sum1=sum1+user[i];
	}

	if
	while(





	if((1==choose)&&(result%2==1)){
		printf("双方开始进攻\n");
	}else if((1==choose)&&(result%2==0))
		printf("玩家选择进攻，电脑选择撤退\n");
		if(result%8==0){
			printf("电脑撤退失败，玩家对电脑造成伤害\n");
		}else{
			printf("电脑撤退成功，玩家此次攻击无效\n");
		}
	}else if((2==choose)&&(result%2==1)){
		printf("玩家选择撤退，电脑选择进攻\n");
		if((result1%4)==0){
			printf("玩家撤退失败，电脑进攻有效\n");
		}else{
			printf("玩家撤退成功，电脑进攻无效\n");
		}
	}else if((2==choose)&&(result%2==0){
		printf("双方选择撤退，这是一个平安夜");
		}





	//每次攻击最多对三人有效
	for(i=0;i<3;i++){
	die=(a%b);
	computer[die]=0;
	}


