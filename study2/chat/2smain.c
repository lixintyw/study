#include "2server.h"
#include "2list.h"
#include "2file.h"

extern List *g_pList;
//使用外部变量

int main(void)
{
	//产生一个链表，用于保存客户端的信息
	g_pList = make_list();
	
	//从链表中获得之前注册的用户数据

	get_usr_info_from_file(USRINFO_PATH,g_pList);
	show_list(g_pList);

	//设置新注册用户的起始id 

	set_base_id();
	//遍历链表，找有无已经生成的id，因为有了id生成的顺序，前面的注定会比后面的小，全局变量一直在变，直到比最后一个大；
	
	int sockfd = make_socket();
	make_bind(sockfd);
	make_listen(sockfd);
	accept_client(sockfd);

	return 0;
}
