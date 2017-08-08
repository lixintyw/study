#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>  //errno

int main(int argc, char *argv[])
{
	//execl("/usr/bin/gedit"
	//	  , "gedit", "./execl.c", NULL);
//	execlp("gedit"
//		  , "gedit", "./execlp.c", NULL);

//	execl("/home/sq/tmp/test", "test", NULL);
	execlp("test", "./test", NULL);


	printf("Hello World\n");

	return 0;
}




