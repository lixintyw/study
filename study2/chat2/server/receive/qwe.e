#include "client.h"


int main(void)
{
	int sockfd = makeSocket();
	connectToServer(sockfd);

	char sign = '\0';
	while (1)
	{
		//login or regist
		loginOrRegist(sockfd);

		//
		chat(sockfd);
		printf("退出程序？Y/y\n");
		getchar();
		sign = getchar();
		getchar();
		if ('y' == sign || 'Y' == sign)
		{
			exitPrograms(sockfd);
			break;
		}
	}
	
	return 0;
}
