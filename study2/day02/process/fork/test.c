#include <stdio.h>
#include <unistd.h>

int main()
{
	int i = 0;
	for (; i < 2; i++)
	{
		fork();
		//printf("g\n");
		printf("g");
	}
	return 0;
}
