#include "server.h"
#include "list.h"
#include "file.h"

extern List *g_pList;

int main(void)
{
	//产生一个链表，用于保存客户端的信息
	g_pList = make_list();

	//从文件中获得之前注册的用户数据
	get_usr_info_from_file(USRINFO_PATH, g_pList);
	show_list(g_pList);

	//设置新注册用户的起始id
	set_base_id();

	int sockfd = make_socket();
	make_bind(sockfd);
	make_listen(sockfd);
	accept_client(sockfd);

	return 0;
}
