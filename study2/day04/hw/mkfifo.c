#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <errno.h>  //errno

int main(int argc, char *argv[])
{
	int ret = mkfifo("myfifo2", 0664);
	if (-1 == ret)
	{
		perror("mkfifo");
		return -1;
	}
	printf("create named pipe ok\n");

	printf("Hello World\n");

	return 0;
}




