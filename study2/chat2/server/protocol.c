#include "protocol.h"

PDU *make_pdu(uint ui_msg_len)
{
	uint ui_pdu_len = sizeof(PDU)-4*sizeof(char)
			        +ui_msg_len;
	PDU *pdu = (PDU *)malloc(ui_pdu_len);
	if (NULL == pdu)
	{
		printf("malloc pdu failed\n");
		exit(EXIT_FAILURE);
	}
	memset(pdu, 0, ui_pdu_len);
	pdu->ui_pdu_len = ui_pdu_len;
	pdu->ui_msg_len = ui_msg_len;
	return pdu;
}
void send_pdu(int sockfd, PDU *pdu)
{
	if (NULL == pdu)
	{
		return;
	}
	int i_sended = 0;
	int i_left = pdu->ui_pdu_len;
	int ret = -1;
	while (i_left)
	{
		if (i_left > PER_MAX_IO_BYTES)
		{
			ret = write(sockfd, (char *)pdu+i_sended
						, PER_MAX_IO_BYTES);
		}
		else
		{
			ret = write(sockfd, (char *)pdu+i_sended
					    , i_left);
		}
		if (-1 == ret)
		{
			perror("send pdu write");
			break;
		}
		i_sended += ret;
		i_left -= ret;
	}
}

PDU *recv_pdu(int sockfd)
{
	uint ui_pdu_len = 0;
	int ret = -1;
	ret = read(sockfd, &ui_pdu_len, sizeof(uint));
	if (0 == ret || -1 == ret)
	{
		return NULL;
	}

	uint ui_msg_len = ui_pdu_len-(sizeof(PDU)-4*sizeof(char));
	PDU *pdu = make_pdu(ui_msg_len);

	int i_recved = sizeof(uint);
	int i_left = ui_pdu_len-sizeof(uint);
	while (i_left)
	{
		if (PER_MAX_IO_BYTES < i_left)
		{
			ret = read(sockfd, (char*)pdu+i_recved
					   , PER_MAX_IO_BYTES);
		}
		else
		{
			ret = read(sockfd, (char*)pdu+i_recved
					   , i_left);	
		}
		if (-1 == ret || 0 == ret)
		{
			break;
		}
		i_recved += ret;
		i_left -= ret;
	}
	return pdu;
}











