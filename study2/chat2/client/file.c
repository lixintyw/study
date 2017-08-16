#include "file.h"

int open_file(const char *pathname, int flags)
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
void save_usr_info_to_file(const char *pathname
				       , const List *list)
{
	if (NULL == list)
	{
		return;
	}

	int fd = open_file(USRINFO_PATH, O_RDWR);

	Node *node = list->pFirst_node;
	while (NULL != node)
	{
		write(fd, node, sizeof(Node));
		node = node->pNext;
	}

	close(fd);
}
void get_usr_info_from_file(const char *pathname
				        , List *list)
{
	if (NULL == list)
	{
		return;
	}

	int fd = open_file(USRINFO_PATH, O_RDWR);

	Node *node = NULL;
	int ret = -1;
	while (1)
	{
		node = make_node();
		ret = read(fd, node, sizeof(Node));
		if (-1 == ret || 0 == ret)
		{
			free(node);
			break;
		}
		node->sockfd = -1;
		node->pNext = NULL;
		insert_list(list, node);
	}
	close(fd);
}






