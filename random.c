#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{   
	int i;	
	srand(time(NULL));
	for(i=0;i<10;i++)
	printf("%5d\n",rand()%101);
	return 0;
}
