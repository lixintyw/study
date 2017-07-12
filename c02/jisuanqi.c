#include<stdio.h>
int main()
{
	float a,b;

	char ch;
	printf("这是一个计算器\n");
	printf("请输入第一个数\n");
	scanf("%f",&a);
	getchar();
	printf("请输入想进行的运算 \t+\t-\t*\t/\n");
	scanf("%c",&ch);
	getchar();
	printf("请输入第二个数\n");
	scanf("%f",&b);
	switch(ch)
	{	
		case '+':printf("运算结果为%0.2f\n",a+b);break;
		case '-':printf("运算结果为%0.2f\n",a-b);break;
		case '*':printf("运算结果为%0.2f\n",a*b);break;
		case '/':printf("运算结果为%0.2f\n",a/b);break;
		default:printf("抱歉，我不知道！\n");
	}
	return 0;
	}
