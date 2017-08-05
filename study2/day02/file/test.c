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
	int ret = -1;
	char caPathname[64] = {'\0'};
	char *p = argv[1];
	//    aa/bb/cc
	//home/sq/aa/bb/cc
	while (1)
	{
		//在字符串a中查找是否存在字符串b
		//若存在，则返回b在a中的地址
		//若不存在，则返回NULL
	//	p = strstr(p, "/");

		p = strchr(p, '/');
		if (NULL != p)
		{
			memset(caPathname, '\0', 64);
			strncpy(caPathname, argv[1], p-argv[1]);
			p++;
			printf("pathname:%s\n", caPathname);
			//access:判断文件是否存在
			//不存在则创建文件
			if (-1 == access(caPathname, F_OK))
			{
				mkdir(caPathname, 0777);
			}
		}
		else
		{
			if (-1 == access(argv[1], F_OK))
			{
				printf("pathname:%s\n", argv[1]);
				mkdir(argv[1], 0777);
			}
			break;
		}
	}

	printf("Hello World\n");

	return 0;
}




