#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

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
	printf("id:%u,name:%s,score:%.2f\n",
				stu->uiId,stu->caName,stu->fScore);
}

int main(int argc,char *argv[])
{
	int fd = -1;
	fd = open(argv[1],O_RDONLY);
	 
	off_t offset = 0;
	off_t size = lseek(fd,offset,SEEK_SET);

	STU tmp;
	read(fd,&tmp,sizeof(STU));
	showStuInfo(&tmp);

	offset = sizeof(STU);
	lseek(fd,offset,SEEK_SET);
	read(fd,&tmp,sizeof(STU));
	showStuInfo(&tmp);
	close(fd);
	return 0;
}
