#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{   
	int i,b,a;	
	srand(time(NULL));
	for(i=0;i<10;i++)
	a=rand();
	b=(a%3);
	switch (b)
	{
		case 0:
		printf("余杰\n");break;
		case 1:	
		printf("三胖\n");break;
		default:
		printf("山炮\n");break;
	}	
	return 0;
}
