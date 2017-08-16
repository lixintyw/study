#include "file.h"

int openFile(const char *pathname, int flags)
{
	int fd = -1;
	fd = open(pathname, flags|O_CREAT, 0664);
	if (-1 == fd)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return fd;
}
void saveUsrInfoToFile(const char *pathname
				       , const List *list)
{
	if (NULL == list)
	{
		return;
	}

	int fd = openFile(USRINFO_PATH, O_RDWR);

	Node *node = list->pFirstNode;
	while (NULL != node)
	{
		write(fd, node, sizeof(Node));
		node = node->pNext;
	}

	close(fd);
}
void getUsrInfoFromFile(const char *pathname
				        , List *list)
{
	if (NULL == list)
	{
		return;
	}

	int fd = openFile(USRINFO_PATH, O_RDWR);

	Node *node = NULL;
	int ret = -1;
	while (1)
	{
		node = makeNode();
		ret = read(fd, node, sizeof(Node));
		if (-1 == ret || 0 == ret)
		{
			free(node);
			break;
		}
		node->sockfd = -1;
		node->pNext = NULL;
		insertList(list, node);
	}
	close(fd);
}






