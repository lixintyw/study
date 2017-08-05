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
	int fd = -1;
	fd  = open(argv[1], O_RDONLY);

	//获得第一个学生	
	off_t offset = 0;
	//设置读写位置在文件首部
	off_t size = lseek(fd, offset, SEEK_SET);
	STU tmp;
	read(fd, &tmp, sizeof(STU));
	showStuInfo(&tmp);
	
	//获得第四个学生
	//offset = 2 * sizeof(STU);
	//lseek(fd, offset, SEEK_CUR);
	offset = 2 * sizeof(STU);
	//设置读写位置距离文件末尾之前的两个学生大小的地方
	lseek(fd, -offset, SEEK_END);
	read(fd, &tmp, sizeof(STU));
	showStuInfo(&tmp);
	
	//获得第二个学生
	//offset = 3 * sizeof(STU);
	//lseek(fd, -offset, SEEK_CUR);
	offset = sizeof(STU);
	lseek(fd, offset, SEEK_SET);
	read(fd, &tmp, sizeof(STU));
	showStuInfo(&tmp);

	close(fd);
	
	return 0;
}
