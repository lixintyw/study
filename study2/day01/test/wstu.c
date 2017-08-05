#include "student.h"
#include "file.h"

int main(int argc, char *argv[])
{
	STU stu[5] = {{1001, "张三", 89}
	              , {1002, "李四", 78}
	              , {1003, "王五", 88}
	              , {1004, "赵六", 98}
	              , {1005, "小七", 77}};

	int fd = openFile(argv[1], O_WRONLY);
	//int fd = open(argv[1], O_WRONLY);
	write(fd, stu, sizeof(stu));
#if 0
	int i = 0;
	for (; i < 5; i++)
	{
		write(fd, stu+i, sizeof(STU));
		//writeDataToFile(fd, stu+i, sizeof(STU));
	}
#endif
	close(fd);

	return 0;
}
