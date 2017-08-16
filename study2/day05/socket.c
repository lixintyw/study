#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>//htons
#include <netinet/in.h>//inet_addr
#include <pthread.h>

void *handle_server(void *arg)
{
	int sockfd = (int)arg;
	char ca_msg[64] = {'\0'};
	int ret = -1;
	while(1)
	{
		ret = read(sockfd,ca_msg,64);
		if(-1 ==  ret||0 == ret)
		{
			break;
		}
		printf("recv msg:%s\n",ca_msg);
	}
}
int main(void)
{
	int sockfd = -1;
	//ipv4,可靠传输,相对应的默认的协议
	//成功返回文件描述符
	//可以想读写文件一样方便的发送和接收数据
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if( -1 == sockfd)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	//设置要连接的服务器的IP地址
	//将点分十进制字符串表示的IP用证书表示
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(8888);
//设置要链接的服务器的端口，用于应用识别
	//hton将数据由本地字节序转化成网络字节序
	//字节序大端字节序和小端字节序
	//将制定大小的空间数据职位0
	bzero(serv_addr.sin_zero,8);
	int ret = -1;
	ret = connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(-1 == ret)
	{
		perror("connect");
		return -1;
	}
	printf("connect to server success\n");
	pthread_t thr;
	pthread_create(&thr,NULL,handle_server,(void *)sockfd);

	

	//char *p_msg = "hello server";
	char ca_msg[64] = {'\0'};
	//往服务器发送信息
	while(1)
	{
		memset(ca_msg,'\0',64);
		read(STDIN_FILENO,ca_msg,64);
		write(sockfd,ca_msg,strlen(ca_msg));
	}

	write(sockfd,ca_msg,strlen(ca_msg));
	read(sockfd,ca_msg,64);
	printf("server says:%s\n",ca_msg);
	return 0;
}

