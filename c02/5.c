#include<stdio.h>
int main()
{
	int i,j,k;
	int	a[9];
	for(i=0;i<10;i++)
		scanf("%d",&a[i]);
	for(i=0;i<10;i++)
	{for(j=0;j<10-i;j++)
					
				if(a[j]<a[j+1])
					{
						k=a[j];
						a[j]=a[j+1];
						a[j+1]=k;
					}				}		
	for(j=0;j<10;j++)
		{
			printf("%d\t",a[j]);
			if(0==((j+1)%5))
				printf("\n");
		}
			
return 0;
}
			
						

