#include<stdio.h>
#include<stdlib.h>
int main()
{   
	int i;	
	for(i=0;i<10;i++)
	printf("%5d\n",rand()%101);
	return 0;
}
