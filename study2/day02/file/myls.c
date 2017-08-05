#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*creat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h> //opendir
#include <errno.h>  //errno

int main(int argc, char *argv[])
{
	int ret = -1;
	//打开一个目录(文件夹)
	DIR *dir = opendir(argv[1]);
	if (NULL == dir)
	{
		perror("opendir");
		return -1;
	}

	struct dirent *pdirent = NULL;
	while (1)
	{
		//循环获得指定目录下的文件信息
		pdirent = readdir(dir);
		if (NULL != pdirent)
		{
			//判断文件的名字是否以d点开头
			//点开头的文件是隐藏文件，
			//不显示直接进入下一次循环
			if (0 == strncmp(".", pdirent->d_name
							 , 1))
			{
				continue;
			}
			printf("%s\t", pdirent->d_name);
			//获得文件类型
			switch (pdirent->d_type)
			{
			case DT_DIR:
				printf("is a directory\n");
				break;
			case DT_REG:
				printf("is a reguler file\n");
				break;
			default:
				printf("is a unknow type\n");
				break;	
			}
		}
		else
		{
			break;
		}
	}
	putchar('\n');
		
	printf("Hello World\n");

	return 0;
}




