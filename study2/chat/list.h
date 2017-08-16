#ifndef LIST_H
#define LIST_H

#include "public.h"

typedef struct Node
{
	uint uiId;
	char caPwd[PWD_LEN];
	int sockfd;
	struct Node *pNext;
}Node;

typedef struct List
{
	int iLen;
	Node *pFirstNode;
}List;

Node *makeNode();
List *makeList();
void insertList(List *list, Node *node);
void showList(const List *list);
Node *findNodeById(uint id, const List *list);

#endif





