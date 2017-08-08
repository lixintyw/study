#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

void cpRegFile(const char *dest, const char *src)
{
	if (NULL == dest || NULL == src)
	{
		return;
	}
	int srcfd = open(src, O_RDONLY);
	int destfd = open(dest, O_WRONLY|O_CREAT, 0664);
	if (-1 == srcfd || -1 == destfd)
	{
		return;
	}
	int ret = -1;
	char caBuf[4096] = {'\0'};
	while (1)
	{
		ret = read(srcfd, caBuf, 4096);
		if (-1 == ret || 0 == ret)
		{
			break;
		}
		write(destfd, caBuf, ret);
	}
	close(srcfd);
	close(destfd);
}

void cpDirFile(const char *destDir
			   , const char *srcDir)
{
	if (NULL == destDir || NULL == srcDir)
	{
		return;
	}
	mkdir(destDir, 0777);

	DIR *pdir = opendir(srcDir);
	if (NULL == pdir)
	{
		perror("opendir");
		return;
	}

	char caSrcPathname[64] = {'\0'};
	char caDestPathname[64] = {'\0'};
	struct dirent *pdirent = NULL;
	while (1)
	{
		pdirent = readdir(pdir);
		if (NULL == pdirent)
		{
			break;
		}
		if (0 == strcmp(".", pdirent->d_name)
		    || 0 == strcmp("..", pdirent->d_name))
		{
			continue;
		}

		memset(caSrcPathname, '\0', 64);
		memset(caDestPathname, '\0', 64);
			
		strcpy(caSrcPathname, srcDir);
		strcat(caSrcPathname, "/");
		strcat(caSrcPathname, pdirent->d_name);

		strcpy(caDestPathname, destDir);
		strcat(caDestPathname, "/");
		strcat(caDestPathname, pdirent->d_name);
	
		printf("src:%s, dest:%s\n", caSrcPathname
						, caDestPathname);

		switch (pdirent->d_type)
		{
		case DT_REG:

			cpRegFile(caDestPathname, caSrcPathname);
			break;
		case DT_DIR:
			cpDirFile(caDestPathname, caSrcPathname);
			break;
		default:
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	if (3 != argc)
	{
		printf("main arg is error\n");
		return -1;
	}

	char *p = strrchr(argv[1], '/');
	char caDestPathname[64] = {'\0'};
	strcpy(caDestPathname, argv[2]);
	strcat(caDestPathname, "/");
	if (NULL == p)
	{
		strcat(caDestPathname, argv[1]);
	}
	else
	{
		p++;
		strcat(caDestPathname, p);
	}
	printf("src:%s, dest:%s\n", argv[1]
						, caDestPathname);
	cpDirFile(caDestPathname, argv[1]);

	return 0;
}
