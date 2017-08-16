#ifndef LIST_H
#define LIST_H

#include "public.h"

typedef struct Node
{
	uint uiId;//分配的id
	char ca_pwd[PWD_LEN];//密码
	int sockfd;//socket号
	struct Node *pNext;
}Node;
//节点用来存放内容
typedef struct List 
{
	int i_len;
	Node *pFirst_node;
}List;
//链表：存放链表长度，和第一个节点

Node *make_node();
List *make_list();
void insert_list(List *list,Node *node);
//插入节点到链表里所以要用节点和链表传参

void show_list(const List *list);
//显示链表里的数据，链表传参，显示对应的节点

Node *find_node_by_id(uint id,const List *list);

#endif


