#include<stdio.h>
int main()
{
	int a,i,k,j;
	printf("要输入的等腰三角形的边为：\n");
	scanf("%d",&a);
	for(i=0;i<a;i++){	
		for(j=0;j<a-i;j++)
				printf(" ");
		for(k=0;k<2*i+1;k++)
		printf("*");
	
	printf("\n");
	}

	return 0;
}
