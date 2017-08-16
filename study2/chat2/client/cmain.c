#include "client.h"


int main(void)
{
	int sockfd = make_socket();
	connect_to_server(sockfd);

	char sign = '\0';
	while (1)
	{
		//login or regist
		login_or_regist(sockfd);

		//
		chat(sockfd);
		printf("退出程序？Y/y\n");
		getchar();
		sign = getchar();
		getchar();
		if ('y' == sign || 'Y' == sign)
		{
			exit_programs(sockfd);
			break;
		}
	}
	
	return 0;
}
