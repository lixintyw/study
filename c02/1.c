#include<stdio.h>
int main()
{
	int i,j,k;
	int a=0;
	printf("1到4可以组成几个不同的三位数\n");
	for(i=1;i<5;i++)
		for(j=1;j<5;j++)
			for(k=1;k<5;k++)
			{
				if(i!=k&&j!=k&&j!=i)
				{
					printf("%d%d%d\t",i,j,k);
             		a++;
				    	if(a%6==0)
				    	printf("\n");
			}   }
	return 0;
}
