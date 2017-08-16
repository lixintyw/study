#ifndef LIST_H
#define LIST_H

#include "public.h"

typedef struct Node
{
	uint uiId;
	char ca_pwd[PWD_LEN];
	int sockfd;
	struct Node *pNext;
}Node;

typedef struct List
{
	int i_len;
	Node *pFirst_node;
}List;

Node *make_node();
List *make_list();
void insert_list(List *list, Node *node);
void show_list(const List *list);
Node *find_node_by_id(uint id, const List *list);

#endif





