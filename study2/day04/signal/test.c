#include <stdio.h>

int myadd(int a, int b)
{
	return a + b;	
}

int *fun(int *, int *)
{

}

typedef unsigned int uint;
typedef int* (*PFUN)(int *, int *)
typedef int * (*)(int *,int *) PFUN
PFUN test()
{
	return fun;
}

int main(void)
{
	printf("sum=%d\n", myadd(34, 67));
	int (*p)(int , int) = myadd;
	int sum = p(12,18);
	printf("sum=%d\n", sum);

	int* (*q)(int*, int*) = fun;
	PFUN m = fun;	

#if 0
	char a = 'a';
	double *p = (double *)&a;
	printf("%d\n", sizeof(p));
	printf("%d\n", sizeof(*p));


	//在地址为0x1024的地方存入一个整数888
	int *p = (int *)0x1024;
	*p = 888;
#endif

	while (1)
	{
		printf("ssssssssss\n");
		sleep(1);
	}
	
	return 0;
}
