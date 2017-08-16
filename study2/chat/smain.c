#include "server.h"
#include "list.h"
#include "file.h"

extern List *g_pList;

int main(void)
{
	//产生一个链表，用于保存客户端的信息
	g_pList = makeList();

	//从文件中获得之前注册的用户数据
	getUsrInfoFromFile(USRINFO_PATH, g_pList);
	showList(g_pList);

	//设置新注册用户的起始id
	setBaseId();

	int sockfd = makeSocket();
	makeBind(sockfd);
	makeListen(sockfd);
	acceptClient(sockfd);

	return 0;
}
