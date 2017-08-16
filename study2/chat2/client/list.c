#include "list.h"

Node *make_node()
{
	Node *node = (Node *)malloc(sizeof(Node));
	if (NULL == node)
	{
		printf("malloc node failed\n");
		exit(EXIT_FAILURE);
	}
	memset(node, 0, sizeof(Node));
	return node;
}

List *make_list()
{
	List *list = (List *)malloc(sizeof(List));
	if (NULL == list)
	{
		printf("malloc list failed\n");
		exit(EXIT_FAILURE);
	}
	memset(list, 0, sizeof(List));
	return list;
}

void insert_list(List *list, Node *node)
{
	if (NULL != list && NULL != node)
	{
		node->pNext = list->pFirst_node;
		list->pFirst_node = node;
		list->i_len++;
	}
}

void show_list(const List *list)
{
	if (NULL == list)
	{
		return;
	}
	Node *node = list->pFirst_node;
	while (NULL != node)
	{
		printf("id:%u, pwd:%s, sockfd:%d\n"
			   , node->uiId, node->ca_pwd
			   , node->sockfd);
		node = node->pNext;
	}
	putchar('\n');
}

Node *find_node_by_id(uint id, const List *list)
{
	Node *node = NULL;
	if (NULL != list)
	{
		node = list->pFirst_node;
		while (NULL != node)
		{
			if (id == node->uiId)
			{
				break;
			}
			node = node->pNext;
		}
	}
	return node;
}





