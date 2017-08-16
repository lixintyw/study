#include "2list.h"
//返回值为节点
Node *make_node()
{
	Node *node = (Node *)malloc(sizeof(Node));
	if(NULL == node)
	{
		printf("malloc node failed\n");
		exit(EXIT_FAILURE);
	}
	memset(node,0,sizeof(Node));
	return node;
}
//创建一个新的节点

List *make_list()
{
	List *list = (List *)malloc(sizeof(List));
	//申请链表空间
	if(NULL == list)
	{
		printf("malloc list failed\n");
		exit(EXIT_FAILURE);
	}
	memset(list,0,sizeof(List));
	return list;
}

void insert_list(List *list,Node *node)
{
	if(NULL != list && NULL != node)
	{
		node->pNext = list->pFirst_node;
		list->pFirst_node = node;
		list->i_len++;
	}
}
//以头插法插入

void show_list(const List *list)
{
	if(NULL == list)
	{
		return;
	}
	Node *node = list->pFirst_node;
//将第一个节点的值传给其他
	while (NULL != node)
	{
		printf("id:%u,pwd:%s,socket:%d\t"
				,node->uiId,node->ca_pwd
				,node->sockfd);
		node = node->pNext;
	}
	putchar('\n');
}
//遍历法传参，依次打印出来

Node *find_node_by_id(uint id,const List *list)
{
	Node *node = NULL;
	if(NULL != list)
	{
		node = list->pFirst_node;
		while(NULL != node)
		{
			if(id == node->uiId)
			{
				break;
			}
			node = node->pNext;
		}
		
	}
	return node;
}
















