#include<stdio.h>
int main()
{
	printf("告诉我你创造的利润\n");
	long int i,b,b1,b2,b3,b4,b5;
	b1=100000*0.1;
	b2=b1+100000*0.075;
	b3=b2+200000*0.05;
	b4=b3+200000*0.03;
	b5=b4+400000*0.015;
	printf("%d\n",b5);
	scanf("%ld",&i);
	if(i<100000)
		b=i*0.1;
	else if(i>=100000&&i<200000)
		b=b1+(i-100000)*0.075;
	else if(i>=200000&&i<400000)
	    b=b2+(i-200000)*0.05;
	else if(i>=400000&&i<600000)
	    b=b3+(i-400000)*0.03;
	else if(i>=600000&&i<1000000)
        b=b4+(i-600000)*0.015;
	else b=b5+(i-1000000)*0.01;
	printf("我们将给你的奖金为%ld\n",b);
	return 0;
}



