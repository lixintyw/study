#include "server.h"
#include "list.h"
#include "protocol.h"
#include "file.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>  //htons

#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
List *g_pList = NULL;
uint g_ui_base_id = 1000;

static void handle_regist_request(int sockfd, PDU *pdu)
{
	//产生节点用于保留客户端的注册信息并存入链表
	//eg: id 和 密码
	Node *node = make_node();
	node->sockfd = -1;
	node->uiId = g_ui_base_id;
	strncpy(node->ca_pwd, pdu->ca_msg, PWD_LEN);
	insert_list(g_pList, node);
	
	//将链表中的数据写入文件
	save_usr_info_to_file(USRINFO_PATH, g_pList);

	//给客户端产生一个注册回复
	PDU *respdu = make_pdu(0);
	respdu->ui_msg_type = ENUM_MSG_TYPE_REGIST_RESPOND;
	respdu->ui_to = g_ui_base_id;
	g_ui_base_id++;
	send_pdu(sockfd, respdu);
	free(respdu);
}

static void handle_login_request(int sockfd, PDU *pdu)
{
	if (NULL == pdu)
	{
		return;
	}
	Node *node = g_pList->pFirst_node;

	while (NULL != node)
	{
		if (node->uiId == pdu->ui_from
		    && 0 == strncmp(node->ca_pwd, pdu->ca_msg, PWD_LEN))
		{
			if (-1 == node->sockfd)
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
	
	if (NULL != node)
	{
		respdu = make_pdu(strlen(LOGIN_OK));
		strncpy(respdu->ca_msg, LOGIN_OK
				, strlen(LOGIN_OK));
	}
	
	else
	{
		respdu = make_pdu(strlen(LOGIN_FAILED));
		strncpy(respdu->ca_msg, LOGIN_FAILED
			    , strlen(LOGIN_FAILED));
	}
	
	respdu->ui_msg_type = ENUM_MSG_TYPE_LOGIN_RESPOND;
	send_pdu(sockfd, respdu);
	free(respdu);
}

static void handle_private_chat_request(int sockfd, PDU *pdu)
{
	if (NULL == pdu)
	{
		return;
	}
	Node *node = g_pList->pFirst_node;
	while (NULL != node)
	{
		if (node->uiId == pdu->ui_to)
		{
			send_pdu(node->sockfd, pdu);
			break;
		}
		node = node->pNext;
	}
}

static void handle_look_request(int sockfd)
{	
	DIR *dir = opendir("./receive");

	if(NULL == dir)
	{
		perror("没有目录!\n");
		return;
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
			{}
			else 
			{
				strcat(msg+i,pdirent->d_name);
				i += 64;
				num++;
			}
		}
		
		else break;
	}
	PDU *pdu = make_pdu(sizeof(msg));
	for(i = 0 ; i < 4096 ; i++)
	{
		pdu->ca_msg[i] = msg[i];
	}
	pdu->file_size = num;
	pdu->ui_msg_type = ENUM_MSG_TYPE_LOOK_FILE_REQUEST;

	send_pdu(sockfd, pdu);
}

static void handle_group_chat_request(int sockfd, PDU *pdu)
{
	if (NULL == pdu)
	{
		return;
	}
	Node *node = g_pList->pFirst_node;
	while (NULL != node)
	{
		if (node->sockfd > 0)
		{
			send_pdu(node->sockfd, pdu);
		}
		node = node->pNext;
	}
}

static void handle_exit_request(int sockfd, PDU *pdu)
{
	if (NULL == pdu)
	{
		return;
	}
	Node *node = find_node_by_id(pdu->ui_from, g_pList);
	if (NULL != node)
	{
		node->sockfd = -1;
	}
}
static void handle_upload(int sockfd,PDU *pdu)
{
	if(NULL == pdu)
	{
		return;
	}
	int fd = -1;
	char ca_name[64]= "./receive/";
	strcat(ca_name,pdu->ca_name);
	
	fd = open(ca_name,O_WRONLY|O_CREAT,0664);
	if(-1 == fd)
	{
		perror("open");
		return;
	}
	
	int writed = 0;
	int left = pdu->file_size;
	int ret = -1;
	while(left)
	{
		if(left > 4096)
		{
			ret = write(fd,(char *)((pdu->ca_msg)+writed),4096);
		}
		
		else
		{
			ret = write(fd,(char *)((pdu->ca_msg)+writed),left);
		}
		
		if(-1 == ret || 0 == ret)
		{
			break;
		}
			
		writed += ret;
		left -= ret;
	}
	
}
static void handle_download(int sockfd,PDU *rvpdu)
{
	int fd = -1;
	char ca_name[64] = "./receive/";
	strcat(ca_name,rvpdu->ca_name);
	fd = open(ca_name,O_RDONLY,0664);
	if(-1 == fd)
	{
		printf("没有该文件\n");
		return;
	}
	unsigned int len = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);
	char buf[4096] = {'\0'};	
	PDU *pdu = make_pdu(len);
	int ret = -1;
	pdu->ui_msg_type = ENUM_MSG_TYPE_DOWNLOAD_REQUEST;
	int i_read = 0;
	int left = len; 
	while(left)
	{
		if(len > 4096)
		{
			ret = read(fd,(char*)buf+i_read,4096);
		}
		else
		{
			ret = read(fd,(char*)buf+i_read,left);
		}
		if(-1 == ret || 0 == ret)
		{
			break;
		}
	 	i_read += ret;
		left -= ret;		
	}
	strcpy(pdu->ca_name,rvpdu->ca_name);
	pdu->file_size = len;
	strncpy(pdu->ca_msg,buf,strlen(buf));
	send_pdu(sockfd,pdu);
	close(fd);
}
static void handle_remove(int sockfd,PDU *pdu)
{	
	int fd = -1;
	char ca_name[64] = "./receive/";
	strcat(ca_name,pdu->ca_name);
	fd = open(ca_name,O_RDONLY,0664);
	if(-1 == fd)
	{
		printf("没有该文件\n");
		return;
	}
	remove(ca_name);
	close(fd);
}
static void handle_rename(int sockfd,PDU *pdu)
{	
  	int fd = -1;
	char ca_name[64] = "./receive/";
	char new_name[64] = "./receive/";
	strcat(ca_name,pdu->ca_name);
	strcat(new_name,pdu->ca_msg);
	
	fd = open(ca_name,O_RDONLY,0664);
	
	if(-1 == fd)
	{
		perror("open");
		return;
	}	
	rename(ca_name,new_name);
	close(fd);

}
static void *handle_client(void *arg)
{
	int sockfd = (int)arg;
	PDU *pdu = NULL;
	while (1)
	{
		//接收客户端的数据
		pdu = recv_pdu(sockfd);
		if (NULL == pdu)
		{
			pthread_exit(NULL);
		}
		//判断消息类型
		//根据消息类型的不同做出不同的处理
		switch (pdu->ui_msg_type)
		{
		//处理客户端的注册请求
			case ENUM_MSG_TYPE_REGIST_REQUEST:
				handle_regist_request(sockfd, pdu);
				break;	
		//处理客户端的登录请求
			case ENUM_MSG_TYPE_LOGIN_REQUEST:
				handle_login_request(sockfd, pdu);
				break;	
		//处理客户端的私聊请求
			case ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST:
				handle_private_chat_request(sockfd, pdu);
				break;	
		//处理客户端的群聊请求
			case ENUM_MSG_TYPE_GROUP_CHAT_REQUEST:
				handle_group_chat_request(sockfd, pdu);
				break;	
		//处理客户端的退出请求
			case ENUM_MSG_TYPE_EXIT_REQUEST:
				handle_exit_request(sockfd, pdu);
				printf("线程退出\n");
				pthread_exit(NULL);
				break;	
			case ENUM_MSG_TYPE_LOOK_FILE_REQUEST:
				handle_look_request(sockfd);
				break;	
			case ENUM_MSG_TYPE_DOWNLOAD_REQUEST:
				handle_download(sockfd, pdu);		
				break;	
			case ENUM_MSG_TYPE_UPLOAD_REQUEST:
				handle_upload(sockfd, pdu);	
				break;	
			case ENUM_MSG_TYPE_REMOVE_REQUEST:
				handle_remove(sockfd, pdu);	
				break;
			case ENUM_MSG_TYPE_RENAME_REQUEST:
				handle_rename(sockfd, pdu);	
				break;
			default:
				break;
		}
		free(pdu);
	}
}

void set_base_id()
{
	Node *node = g_pList->pFirst_node;
	int sign = 0;
	while (NULL != node)
	{
		if (g_ui_base_id < node->uiId)
		{
			g_ui_base_id = node->uiId;
			sign = 1;
		}	
		node = node->pNext;
	}
	if (1 == sign)
	{
		g_ui_base_id++;
	}
}

int make_socket()
{
	//产生socket用于监听客户端的连接
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	return sockfd;
}

void make_bind(int sockfd)
{
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(8888);
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(servAddr.sin_zero, 8);

	//将sockfd和特定的ip及端口绑定
	//表示通过该scokfd来监听从绑定的ip连接过来的
	//作用于指定端口的客户端
	int ret = -1;
	ret = bind(sockfd
			   , (struct sockaddr *)&servAddr
			   , sizeof(servAddr));
	if (-1 == ret)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
}

void make_listen(int sockfd)
{
	//设置该sockfd每次能够处理的最大客户端数
	int ret = listen(sockfd, 10);
	if (-1 == ret)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
}

void accept_client(int sockfd)
{
	struct sockaddr_in client_addr;
	int client_sockfd = -1;
	int i_len = sizeof(client_addr);
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
		
		client_sockfd = accept(sockfd,(struct sockaddr *)&client_addr,&i_len);
		
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
