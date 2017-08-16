#include "list.h"

Node *makeNode()
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

List *makeList()
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

void insertList(List *list, Node *node)
{
	if (NULL != list && NULL != node)
	{
		node->pNext = list->pFirstNode;
		list->pFirstNode = node;
		list->iLen++;
	}
}

void showList(const List *list)
{
	if (NULL == list)
	{
		return;
	}
	Node *node = list->pFirstNode;
	while (NULL != node)
	{
		printf("id:%u, pwd:%s, sockfd:%d\t"
			   , node->uiId, node->caPwd
			   , node->sockfd);
		node = node->pNext;
	}
	putchar('\n');
}

Node *findNodeById(uint id, const List *list)
{
	Node *node = NULL;
	if (NULL != list)
	{
		node = list->pFirstNode;
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





