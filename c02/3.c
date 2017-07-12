#include<stdio.h>
#include<math.h>
int main()
{
	long int i,x,y,z;
	for(i=0;i<100000;i++)
	{
		x=sqrt(i+100);
		y=sqrt(i+225);
		if(x*x==(i+100)&&y*y==(i+225))
			printf("该数为%ld\n",i);
	return 0;
	}
}

