#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>  //htons
#include <pthread.h>
#include "client.h"
#include "protocol.h"
#include "file.h"
uint g_uiId = 0;

static void handle_chat(PDU *pdu)
{
	if (NULL == pdu)
	{
		return;
	}
	printf("%u says: \n", pdu->ui_from);
	write(STDOUT_FILENO, pdu->ca_msg, pdu->ui_msg_len);
}
static void handle_file(PDU *pdu)
{
	if(NULL == pdu)
	{
		return;
	}
	printf("文件:\n");
	
	int i = 0 , j = 0;
	
	for(i = 0 ; i < pdu->file_size ; i++)
	{
		printf("%s\t",pdu->ca_msg+j);
		j += 64;
	}
	printf("\n");
}

static void handle_download(PDU *pdu)
{
	if(NULL == pdu)
	{
		return;
	}
	int fd = -1;
	char ca_name[64]= "./download/";
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
// 循环接收服务器的信息并处理
void *handle_server(void *arg)
{
	int sockfd = (int)arg;
	PDU *pdu = NULL;
	while (1)
	{
		//   接收服务器的消息
	 	pdu = recv_pdu(sockfd);
		if (NULL == pdu)
		{
			printf("和服务器已断开\n");
			exit(0);
		}
		//根据消息的类型做出不同的处理
		switch (pdu->ui_msg_type)
		{
		//处理服务器返回的注册回复信息
			case ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST:
			case ENUM_MSG_TYPE_GROUP_CHAT_REQUEST:
				handle_chat(pdu);
				break;
			case ENUM_MSG_TYPE_LOOK_FILE_REQUEST:
				handle_file(pdu);
				break;	
			case ENUM_MSG_TYPE_DOWNLOAD_REQUEST:
				handle_download(pdu);
				printf("下载完成\n");
				break;
			default:
				break;
		}
		free(pdu);
	}
}

int make_socket()
{
	//AF_INET:ipv4
	//SOCK_STREAM:使用可靠传输-->tcp
	//SOCK_DGRAM:非可靠传输-->udp
	//0: 使用传输默认的协议
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	return sockfd;
}

void connect_to_server(int sockfd)
{
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	//htons:表示将主机字节序转换为网络字节序
	//字节序：大端字节序，小端字节序
	//端口用来标识应用
	servAddr.sin_port = htons(8888);
	//设置要连接的服务器的ip地址
	//inet_addr:将点分十进制表示的ip转换成整数表示
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//将指定地址的开始往后的多少个字节置为0
	bzero(servAddr.sin_zero, 8);

	int ret = -1;
	//连接服务器
	ret = connect(sockfd
				  , (struct sockaddr *)&servAddr
	              , sizeof(servAddr));
	if (-1 == ret)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	printf("成功连接服务器\n");
}

int login_or_regist_face()
{
	printf("  欢迎\n");
	printf("1,登录\n");
	printf("2,注册\n");
	printf("0,退出\n");
	printf("请输入选项:\n");
	int num = 0;
	scanf("%d", &num);
	return num;
}
 
static void regist(int sockfd)
{
	PDU *pdu = make_pdu(PWD_LEN);
	pdu->ui_msg_type = ENUM_MSG_TYPE_REGIST_REQUEST;
	printf("请输入注册需要的密码：\n");
	scanf("%s", pdu->ca_msg);
	send_pdu(sockfd, pdu);
	free(pdu);

	pdu = recv_pdu(sockfd);
    if (ENUM_MSG_TYPE_REGIST_RESPOND
         == pdu->ui_msg_type)
	{
		g_uiId = pdu->ui_to;
		printf("获得注册的id: %u\n", g_uiId);
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
	scanf("%u", &pdu->ui_from);
	id = pdu->ui_from;
	printf("请输入密码:\n");
	scanf("%s", pdu->ca_msg);
	pdu->ui_msg_type = ENUM_MSG_TYPE_LOGIN_REQUEST;
	send_pdu(sockfd, pdu);
	free(pdu);

	pdu = recv_pdu(sockfd);
	if (ENUM_MSG_TYPE_LOGIN_RESPOND 
	    && 0 == strncmp(LOGIN_OK, pdu->ca_msg
				        , pdu->ui_msg_len))
	{
		printf("登录成功\n");
		g_uiId = id;
		return 1;
	}
	printf("登录失败\n");
	write(STDOUT_FILENO, pdu->ca_msg, pdu->ui_msg_len);
	putchar('\n');

	return -1;
}

void exit_programs(int sockfd)
{
	PDU *pdu = make_pdu(0);
	pdu->ui_from = g_uiId;
	pdu->ui_msg_type = ENUM_MSG_TYPE_EXIT_REQUEST;
	send_pdu(sockfd, pdu);
	free(pdu);
	printf("发送退出请求\n");	
}

void login_or_regist(int sockfd)
{
	int num = -1;
	int ret = -1;
	while (1)
	{
		num = login_or_regist_face();
		switch (num)
		{
		case 1:
			ret = login(sockfd);
			break;
		case 2:
			regist(sockfd);
			break;
		case 0:
			exit_programs(sockfd);
			exit(EXIT_SUCCESS);
		default:
			printf("输入有误!!!\n");
			break;
		}
		if (1 == ret)
		{
			break;
		}
	}
}

static int chat_face()
{
	printf("-------------\n");
	printf("1:私聊\n");
	printf("2:群聊\n");
	printf("3:群文件\n");
	printf("4:下载文件\n");
	printf("5:上传文件\n");
	printf("6:重命名文件\n");
	printf("7:删除文件\n");
	printf("0:返回\n");
	printf("请输入选项:\n");
	int num = 0;
	scanf("%d", &num);
	return num;
}
static void download(int sockfd)
{
	PDU *pdu = make_pdu(sizeof(PDU));
	printf("请输入下载的文件名:\n");
	scanf("%s",pdu->ca_name);

	pdu->ui_from = g_uiId;
	pdu->ui_msg_type = ENUM_MSG_TYPE_DOWNLOAD_REQUEST;
	send_pdu(sockfd, pdu);
	free(pdu);
}
static void private_chat(int sockfd)
{
	printf("请输入聊天的对象:\n");
	uint perid = 0;
	scanf("%u", &perid);

	char ca_msg[PER_MAX_IO_BYTES] = {'\0'};
	printf("请输入聊天信息:\n");
	read(STDIN_FILENO, ca_msg
	     , PER_MAX_IO_BYTES);
	PDU *pdu = make_pdu(strlen(ca_msg));
	pdu->ui_from = g_uiId;
	pdu->ui_to = perid;
	strncpy(pdu->ca_msg, ca_msg, strlen(ca_msg));
	pdu->ui_msg_type = ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST;
	send_pdu(sockfd, pdu);
	free(pdu);
}

static void group_chat(int sockfd)
{
	char ca_msg[PER_MAX_IO_BYTES] = {'\0'};
	printf("请输入聊天信息:\n");
	read(STDIN_FILENO, ca_msg
	     , PER_MAX_IO_BYTES);
	PDU *pdu = make_pdu(strlen(ca_msg));
	pdu->ui_from = g_uiId;
	strncpy(pdu->ca_msg, ca_msg, strlen(ca_msg));
	pdu->ui_msg_type = ENUM_MSG_TYPE_GROUP_CHAT_REQUEST;
	send_pdu(sockfd, pdu);
	free(pdu);
}
void look_file(int sockfd)
{
	PDU *pdu = make_pdu(1);
	pdu->ui_from = g_uiId;
	pdu->ui_msg_type = ENUM_MSG_TYPE_LOOK_FILE_REQUEST;
	send_pdu(sockfd, pdu);
	free(pdu);
}
void upload_file(int sockfd)
{
	char ca_name[64] = {'\0'};
	printf("请输入文件名\n");
	scanf("%s",ca_name);
	while(getchar() != '\n');
	
	
	int fd = -1;
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
	pdu->ui_msg_type = ENUM_MSG_TYPE_UPLOAD_REQUEST;
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
	strcpy(pdu->ca_name,ca_name);
	pdu->file_size = len;
	strncpy(pdu->ca_msg,buf,strlen(buf));
	send_pdu(sockfd,pdu);
	close(fd);
}
void rename_file(int sockfd)
{	
	char ca_name[64] = {'\0'};
	char new_name[64] = {'\0'};
	printf("请输入文件名\n");
	scanf("%s",ca_name);
	while(getchar() != '\n');
	
	printf("请输入新名字\n");
	scanf("%s",new_name);
	while(getchar() != '\n');
	
	
	PDU *pdu = make_pdu(sizeof(new_name));
	pdu->ui_msg_type = ENUM_MSG_TYPE_RENAME_REQUEST;
	strncpy(pdu->ca_name,ca_name,strlen(ca_name));		
	strncpy(pdu->ca_msg,new_name,strlen(new_name));	
	send_pdu(sockfd,pdu);
}
void remove_file(int sockfd)
{
	char ca_name[64] = {'\0'};
	printf("请输入文件名\n");
	scanf("%s",ca_name);
	while(getchar() != '\n');
	
	PDU *pdu = make_pdu(1);
	pdu->ui_msg_type = ENUM_MSG_TYPE_REMOVE_REQUEST;
	strncpy(pdu->ca_name,ca_name,strlen(ca_name));	
	send_pdu(sockfd,pdu);
}
void chat(int sockfd)
{
	pthread_t thread;
	pthread_create(&thread, NULL, handle_server
				   , (void *)sockfd);

	int num = -1;
	while (1)
	{
		num = chat_face();
		switch (num)
		{
		case 1:
			private_chat(sockfd);
			break;
		case 2:
			group_chat(sockfd);
			break;
		case 3:
			look_file(sockfd);
			break;
		case 4:
			download(sockfd);
			break;
		case 5:
			upload_file(sockfd);
			break;
		case 6:
			rename_file(sockfd);
			break;
		case 7:
			remove_file(sockfd);
			break;
		case 0:
			pthread_cancel(thread);
			return;
		default:
			break;
		}
	}
}



