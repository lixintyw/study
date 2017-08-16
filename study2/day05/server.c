#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netinet/in.h>

void *handle_client(void *arg)
		
{
	int sockfd = (int)arg;
	char ca_msg[64] = {'\0'};
	int ret = 0;
	while(1)
	{
		memset(ca_msg,'\0',64);
		ret = read(sockfd,ca_msg,64);
		if(-1 == ret||0 == ret)
		{
			break;
		}
		strcat(ca_msg, " >_< ");
		write(sockfd,ca_msg,strlen(ca_msg));
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
//设置要监听的服务器的端口，用于应用识别
	//hton将数据由本地字节序转化成网络字节序
	//字节序大端字节序和小端字节序
	//将制定大小的空间数据职位0
	bzero(serv_addr.sin_zero,8);
	int ret = -1;
	//设置要监听的服务器的端口
	ret = bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(-1 == ret)
	{
		perror("connect");
		return -1;
	}

	listen(sockfd,10);
	//表示服务器每次可以处理的最多的客户端数
	//并且使sockfd处于监听状态

	printf("connect to server success\n");


	struct sockaddr_in client_addr;

	int i_len = sizeof(client_addr);
	int client_sockfd = -1;

	char ca_msg[64] = {'\0'};
	pthread_t thr;
	while(1)
	{
		printf("接收客户端的链接\n");
		client_sockfd = accept(sockfd
						,(struct sockaddr*)&client_addr
						,&i_len);

		if(-1 == client_sockfd)
		{
			perror("accept");
			break;
		}
	printf("ip为%s的客户端连接到服务器\n"
					,inet_ntoa(client_addr.sin_addr));
	printf("新产生的socket 为 = %d\n",client_sockfd);
	//接收客户端发送来的信息
	//char ca_msg[64] = {'\0'};
//	read(client_sockfd,ca_msg,64);
//	strcat(ca_msg,"~^_^~");
	//往客户端发数据

	pthread_create(&thr,NULL,handle_client,(void*)client_sockfd);
	//write(sockfd,ca_msg,strlen(ca_msg));
	}
	return 0;
}

