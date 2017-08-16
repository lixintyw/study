#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>//htons

#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include "2client.h"
#include "2protocol.h"
#include <pthread.h>
uint g_uiId = 0;

//static int file_face()
int login_or_regist_face();
void handle_look_file(PDU *pdu);
//static void regist(int sockfd);
//static int login(int sockfd);
//static void look_file(sockfd);
//static void download_file(sockfd);
//static void upload_file(sockfd);
//static void delete_file(sockfd);
//static void change_filename(sockfd);
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


void connect_to_server(int sockfd)
{
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	//htons 表示将主机字节序转换为网络字节序
	serv_addr.sin_port = htons(8888);
	//设置要链接的服务器的IP地址
	//inet_addr 将点分十进制表示的IP转换成整数表示
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero (serv_addr.sin_zero,8);

	int ret = -1;
	ret = connect(sockfd
					,(struct sockaddr*)&serv_addr
					,sizeof(serv_addr));
	if(-1 == ret)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	printf("connect to server success\n");
}

int login_or_regist_face()
{
	printf(" 欢迎\n");
	printf("1,登录\n");
	printf("2,注册\n");
	printf("0,退出\n");
	printf("请输入选项：\n");
	int num = 0;
	scanf("%d",&num);
	return num ;
}
static void regist(int sockfd)
{
	PDU *pdu = make_pdu(PWD_LEN);//传参传的是信息里的长度
	pdu->ui_msg_type = ENUM_MSG_TYPE_REGIST_REQUEST;
	printf("请输入注册需要的密码：\n");
	scanf("%s",pdu->ca_msg);
	while(getchar()!='\n');
	send_pdu(sockfd,pdu);
	free(pdu);

	pdu = recv_pdu(sockfd);
	if(ENUM_MSG_TYPE_REGIST_RESPOND == pdu->ui_msg_type)
	{
		g_uiId = pdu->ui_to;
		printf("获得注册的id：%u\n",g_uiId);
	}
	else
	{
		printf("注册失败\n");
	}
	free(pdu);
}

static int login(int sockfd)
{
	int id = 0;
	PDU *pdu = make_pdu(PWD_LEN);
	printf("请输入id:\n");
	scanf("%u",&pdu->ui_from);
	while(getchar()!='\n');
	id = pdu->ui_from;
	printf("请输入密码：\n");
	scanf("%s",pdu->ca_msg);
	while(getchar()!='\n');
	pdu->ui_msg_type = ENUM_MSG_TYPE_LOGIN_REQUEST;
	send_pdu(sockfd,pdu);
	free(pdu);

	pdu = recv_pdu(sockfd);
	if(ENUM_MSG_TYPE_LOGIN_RESPOND
		&&0 == strncmp(LOGIN_OK,pdu->ca_msg
				,pdu->ui_msg_len))
	{
		printf("登陆成功\n");
		g_uiId = id;
		return 1;
	}
	printf("登录失败\n");
	write(STDOUT_FILENO,pdu->ca_msg,pdu->ui_msg_len);
	putchar('\n');

	return -1;
}
void exit_programs(int sockfd)
{
	PDU *pdu = make_pdu(0);
	pdu->ui_from = g_uiId;
	pdu->ui_msg_type = ENUM_MSG_TYPE_EXIT_REQUEST;
	send_pdu(sockfd,pdu);
	free(pdu);
	printf("发送退出请求\n");
}
void login_or_regist(int sockfd)
{
	int num = -1;
	int ret = -1;
	while(1)
	{
		num = login_or_regist_face();
		switch(num)
		{
			case 1:
				ret = login(sockfd);
				break;
				//有返回值
			case 2:
				regist(sockfd);
				break;
			case 0:
				exit_programs(sockfd);
				exit(EXIT_SUCCESS);
			default:
				printf("输入有无！！！！\n");
				break;
		}
		if(1 == ret)
		{
			break;
		}

	}
}




//static void handle_chat(PDU *pdu)
//{
//	if(NULL == pdu)
//	{
//		return;
//	}
//	printf("%u says : \n",pdu->ui_from);
//	write(STDOUT_FILENO,pdu->ca_msg,pdu->ui_msg_len);
//}


void *handle_server(void *arg)
{
	int sockfd = (int)arg;
	PDU *pdu = NULL;
	while(1)
	{
		pdu = recv_pdu(sockfd);
		if(NULL == pdu)
		{
			printf("和服务器断开\n");
			exit(0);
		}
		switch(pdu->ui_msg_type)
		{
				case ENUM_MSG_TYPE_LOOK_FILE_REQUEST:
				handle_look_file(pdu);
				break;
			default:
				break;
		}
		free(pdu);
	}
}

void handle_look_file(PDU *pdu)
{
	if(NULL == pdu)
	{
		return ;
	}
	printf("文件\n");
	int i = 0;
	int j = 0;
	for(i = 0;i < pdu->file_size;i++)
	{
		printf("%s\t",pdu->ca_msg+j);

		j = j+64;
	}
//	write(STDOUT_FILENO,pdu->ca_msg,pdu->ui_msg_len);
//	printf("%d",pdu->ui_to);
	return;
}

static void look_file(int sockfd)
{
	PDU *pdu = make_pdu(0);
	pdu->ui_from = g_uiId;
	pdu->ui_msg_type = ENUM_MSG_TYPE_LOOK_FILE_REQUEST;
	write(sockfd,pdu,pdu->ui_pdu_len);
	send_pdu(sockfd,pdu);
	free(pdu);
}

static void download_file(int sockfd)
{
	}
static int file_face()
{
	printf(" ^_^ \n");
	printf("1,查看文件\n");
	printf("2,下载文件\n");
	printf("3,上传文件\n");
	printf("4,删除文件\n");
	printf("5,改变文件名\n");
	printf("0,返回\n");
	printf("请输入选项:\n");
	int num = 0;
	scanf("%d",&num);
	while(getchar()!='\n');
	return num;
}
void file(int sockfd)
{
	pthread_t thread;
	int num = -1;
	while(1)
	{
		num = file_face();
		switch (num)
		{
			case 1:
				look_file(sockfd);
				break;
			case 2:
//				download_file(sockfd);
				break;
			case 3:
//				upload_file(sockfd);
				break;
			case 4:
//				delete_file(sockfd);
				break;
			case 5:
//				change_filename(sockfd);
			case 0:
				pthread_cancel(thread);
				return;
			default:
				break;
		}
	}
	//创建新的线程，调用前面的处理函数
	pthread_create(&thread,NULL,handle_server
					,(void *)sockfd);
	//调用一个函数handle_server用来处理关于文件的所有操作
}










	
