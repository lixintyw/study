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
	STU stu[5] = {{1001, "张三", 89}
	              , {1002, "李四", 78}
	              , {1003, "王五", 88}
	              , {1004, "赵六", 98}
	              , {1005, "小七", 77}};

	int fd = open(argv[1], O_WRONLY|O_CREAT, 0664);
	write(fd, stu, sizeof(stu));
	close(fd);

	return 0;
}
