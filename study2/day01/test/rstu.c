#include "student.h"
#include "file.h"

int main(int argc, char *argv[])
{
//	int fd = openFile(argv[1], O_RDONLY);
	int fd = open(argv[1], O_RDONLY);
	
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
