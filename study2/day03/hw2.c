
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>


void cp_reg_file(const char *dest,const char *src);
void cp_dirfile(const char *dest_dir,const char *src_dir);
int main(int argc,char *argv[])
{
	if (3 != argc)
	{
		printf("main arg is error\n");
		return -1;
	}

	char *p = strrchr(argv[1],'/');
	char ca_dest_pathname[64] = {'\0'};

	strcpy(ca_dest_pathname,argv[2]);
	strcat(ca_dest_pathname,"/");

	if(NULL == p)
	{
		strcat(ca_dest_pathname,argv[1]);
	}
	else
	{
		p++;
		strcat(ca_dest_pathname,p);
	}

	printf("src:%s,dest:%s",argv[1],ca_dest_pathname);

	cp_dirfile(ca_dest_pathname,argv[1]);

	return 0;
}


void cp_dirfile(const char *dest_dir,const char *src_dir)
{
	if(NULL == dest_dir || NULL == src_dir)
	{
		return 0;
	}
	mkdir(dest_dir,0777);//budong

	DIR *pdir = opendir(src_dir);
	if(NULL == pdir)
	{
		perror("open dir");
		return;
	}

	char ca_src_pathname[64] = {'\0'};
	char ca_dest_pathname[64] = {'\0'};

	struct dirent *pdirent = NULL;

	while(1)
	{
		pdirent = readdir(pdir);
		if(NULL == pdirent)
		{
			break;
		}
		if(0 == strcmp(".",pdirent->d_name);
			|| 0 == strcmp("..",pdirent->d_name))
		{
			continue;
		}

		memset(ca_src_pathname,'\0',64);
		memset(ca_dest_pathname,'\0',64);

		strcpy(ca_src_pathname,src_dir);
		strcat(ca_src_pathname,"/");
		strcat(ca_src_pathname,pdirent->d_name);
		
		strcpy(ca_dest_pathname,dest_dir);
		strcat(ca_dest_pathname,"/");
		strcat(ca_dest_pathname,pdirent->d_name);
		
		printf("src:%s,dest:%s\n",ca_src_pathname,ca_dest_pathname);

		switch(pdirent->d_type)
		{
			case DT_REG:
				cp_reg_file(ca_dest_pathname,ca_src_pathname);
				break;
			case DT_DIR:
				cp_dir_file(ca_dest_pathname,ca_src_pathname);
				break;
			default:
				break;
		}
	}
}

void cp_reg_file(const char *dest,const char *src)
{
	if(NULL == dest || NULL == src)
	{
		return;
	}

	int srcfd = open(src,O_RDONLY);
	int destfd = open(dest,O_WRONLY|O_CREAT,0664);
	if(-1 == srcfd || -1 == destfd)
	{
		return;
	}
	int ret = -1;
	char ca_buf[4096] = {'\0'};
	while(1)
	{
		ret = read(srcfd,ca_buf,4096);
		if(-1 == ret || 0 == ret)
		{
			break;
		}
		write(destfd,ca_buf,ret);
	}
	close(srcfd);
	close(destfd);
}

			








