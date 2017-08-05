#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>  //errno

typedef unsigned int uint;
#define NAME_LEN 32
typedef struct Student
{
	uint uiId;
	char caName[NAME_LEN];
	float fScore;
}STU;

void showStuInfo(const STU *stu)
{
	printf("id:%u, name:%s, score:%.2f\n"
		   , stu->uiId, stu->caName, stu->fScore);
}

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDONLY|O_CREAT, 0664);
	
	STU tmp;
	int ret = -1;
	while (1)
	{
		ret = read(fd, &tmp, sizeof(STU));
		if (-1 == ret || 0 == ret)
		{
			break;
		}
		showStuInfo(&tmp);
	}

	close(fd);

	return 0;
}
