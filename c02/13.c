#include<stdio.h>
int main()
{
	int i,j,n;
	printf("\nplease input a number:");
	scanf("%d",&n);
	printf("/n%d=",n);
	for(i=2;i<=n;i++)
		{
			while(n!=i)
				{
					if(n%i==0)
						{
							printf("%d*",i);
							n=n/i;
						}else
							break;
				}
		}
	printf("%d",n);
	return 0;
}
	
