#include "2server.h"
#include "2list.h"
#include "2protocol.h"
#include "2file.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>

List *g_pList = NULL;
uint g_ui_base_id = 1000;


//static void handle_exit_request(int sockfd,PDU *pdu);
//static void handle_regist_request(int sockfd,PDU *pdu);
//static void handle_login_request(int sockfd,PDU *pdu);
//static void handle_look_file_request(int sockfd,PDU *pdu);
//static void *handle_client(void *arg);
static void handle_regist_request(int sockfd,PDU *pdu)
{
	//产生节点用于保留客户端的注册信息并存入链表
	Node *node = make_node();
	node->sockfd = -1;
	node->uiId = g_ui_base_id;
	strncpy(node->ca_pwd,pdu->ca_msg,PWD_LEN);
	insert_list(g_pList,node);

	//将链表数据写入文件

	save_usr_info_to_file(USRINFO_PATH,g_pList);
	//给客户端产生一个注册回复

	PDU *respdu = make_pdu(0);
	respdu->ui_msg_type = ENUM_MSG_TYPE_REGIST_RESPOND;
	respdu->ui_to = g_ui_base_id;
	g_ui_base_id++;
	send_pdu(sockfd,respdu);
	free(respdu);
}

static void handle_login_request(int sockfd,PDU *pdu)
{
	if(NULL == pdu)
	{
		return ;
	}
	Node *node = g_pList->pFirst_node;
	while(NULL != node)
	{
		if(node->uiId == pdu->ui_from
				&&0 == strncmp(node->ca_pwd,pdu->ca_msg,PWD_LEN))
		{
			if(-1 == node->sockfd)
			{
				node->sockfd = sockfd;
			}
			else
			{
				node = NULL;
			}
			break;
		}
		node = node->pNext;
	}
	PDU *respdu = NULL;
	if(NULL!= node)
	{
		respdu = make_pdu(strlen(LOGIN_OK));
		strncpy(respdu->ca_msg,LOGIN_OK
							,strlen(LOGIN_OK));
	}
	else
	{
		respdu = make_pdu(strlen(LOGIN_OK));
		strncpy(respdu->ca_msg,LOGIN_FAILED
							,strlen(LOGIN_FAILED));
	}
	respdu->ui_msg_type = ENUM_MSG_TYPE_LOGIN_RESPOND;
	send_pdu(sockfd,respdu);
	free(respdu);
}

static void handle_exit_request(int sockfd,PDU *pdu)
{
	if(NULL == pdu)
	{
		return;
	}
	Node *node = find_node_by_id(pdu->ui_from,g_pList);
	if(NULL != node)
	{
		node->sockfd = -1;
	}
}

static void handle_look_file_request(int sockfd,PDU *pdu)
{
		DIR *dir = opendir("./");
		if(NULL == dir)
		{
			perror("dir");
			return ;
		}
		char msg[4096] = {'\0'};
		struct dirent *pdirent = NULL;
		int i = 0;
		int num = 0;
		while(1)
		{
			pdirent = readdir(dir);
			if(NULL != pdirent)
			{
				if(0 == strncmp(".",pdirent->d_name,1))
				{
					
				}
				strcat(msg+i,pdirent->d_name);
		//		printf("%s\n",msg+i);
		i = i+64;
				num++;
			}
			else
				break;
		}
	pdu = make_pdu(sizeof(msg));
		for(i = 0;i < 4096;i++)
		{
			pdu->ca_msg[i] = msg[i];
		}
		pdu->file_size = num;
		pdu->ui_msg_type = ENUM_MSG_TYPE_LOOK_FILE_REQUEST;
		send_pdu(sockfd,pdu);
} 

	
static void *handle_client(void *arg)
{
	int sockfd = (int)arg;
	PDU *pdu = NULL;
	while(1)
	{
		//接收客户端数据
		pdu = recv_pdu(sockfd);
		if(NULL == pdu)
		{
			pthread_exit(NULL);
			//如果没有消息则退出线程
		}
		//判断消息类型
		//根据不同的消息类型的不同做出不同的处理
		switch(pdu->ui_msg_type)
		{
			//依次处理客户端的请求

		//处理客户端的注册请求
		case ENUM_MSG_TYPE_REGIST_REQUEST:
			handle_regist_request(sockfd, pdu);
			break;	
		//处理客户端的登录请求
		case ENUM_MSG_TYPE_LOGIN_REQUEST:
			handle_login_request(sockfd, pdu);
			break;	
		//处理客户端的私聊请求
//		case ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST:
//			handle_private_chat_request(sockfd, pdu);
//			break;	
		//处理客户端的群聊请求
//		case ENUM_MSG_TYPE_GROUP_CHAT_REQUEST:
//			handle_group_chat_request(sockfd, pdu);
//			break;	
		case ENUM_MSG_TYPE_LOOK_FILE_REQUEST:
			handle_look_file_request(sockfd,pdu);
			break;
		case ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST:
//			handle_download_file_request(sockfd.pdu);
			break;

		case ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST:
//			handle_upload_file_request(sockfd,pdu);
			break;

		case ENUM_MSG_TYPE_DELETE_FILE_REQUEST:
//			handle_delete_file_request(sockfd,pdu);
			break;
		case ENUM_MSG_TYPE_CHANGE_FILENAME_REQUEST:
//			handle_change_filename_request(sockfd,pdu);
			break;
			
			//处理客户端的退出请求
		


		case ENUM_MSG_TYPE_EXIT_REQUEST:
			handle_exit_request(sockfd, pdu);
			printf("线程退出\n");
			pthread_exit(NULL);
			break;	
		default:
			break;
		}
		free(pdu);
	}
}
//处理的关键步骤

void set_base_id()
{
	Node *node = g_pList->pFirst_node;
	int sign = 0;
	while(NULL != node)
	{
		if(g_ui_base_id < node->uiId)
		{
			g_ui_base_id = node->uiId;
			sign = 1;
		}
		node = node->pNext;
	}
	if(1 == sign)
	{
		g_ui_base_id++;
	}
}

//创建一个socket用于监听客户端的链接

int make_socket()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == sockfd)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	return sockfd;
}

void make_bind(int sockfd)
{
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8888);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(serv_addr.sin_zero,8);
	//将sockfd和特定的ip及端口绑定
	//表示通过该sockfd来监听从绑定的IP链接过来的作用于制定端口的客户端
	int ret = -1;
	ret = bind(sockfd
				,(struct sockaddr *)&serv_addr
				,sizeof(serv_addr));
	if(-1 == ret)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

}

void make_listen(int sockfd)
{
	//设置该socket 每次可以处理的最大客户端数
	int ret = listen(sockfd,10);
	if(-1 == ret)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
}

void accept_client(int sockfd)
{
	struct sockaddr_in client_addr;
	int client_sockfd = -1;
	int iLen = sizeof(client_addr);
	pthread_t thread;
	while (1)
	{
		printf("等待客户端的连接...\n");
		//阻塞等待客户端的连接
		//若有客户端连接过来，
		//则会自动将客户端的相应信息存入clientAddr中
		//然后往下执行
		//若有客户端连接服务器成功
		//则产生一个新的socket
		//该新的socket用于服务器和客户端数据交换
		client_sockfd = accept(sockfd
					, (struct sockaddr *)&client_addr
					, &iLen);
		if (-1 == client_sockfd)
		{
			perror("accept");
			break;
		}
		//inet_ntoa:将整形表示的ip
		//          转换成点分十进制表示的ip
		printf("ip为%s的客户端连接到服务器\n"
			   , inet_ntoa(client_addr.sin_addr));
		
		printf("产生的新的用于数据交换的sockfd:%d\n"
			   , client_sockfd);
		
		//每来一个客户端的连接
		//创建一个新的线程来专门处理该客户端
		pthread_create(&thread, NULL
					, handle_client
					, (void *)client_sockfd);
	}
}
//调用了一个handle_client 函数

	


































