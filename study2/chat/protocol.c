#include "protocol.h"

PDU *makePDU(uint uiMsgLen)
{
	uint uiPDULen = sizeof(PDU)-4*sizeof(char)
			        +uiMsgLen;
	PDU *pdu = (PDU *)malloc(uiPDULen);
	if (NULL == pdu)
	{
		printf("malloc pdu failed\n");
		exit(EXIT_FAILURE);
	}
	memset(pdu, 0, uiPDULen);
	pdu->uiPDULen = uiPDULen;
	pdu->uiMsgLen = uiMsgLen;
	return pdu;
}
void sendPDU(int sockfd, PDU *pdu)
{
	if (NULL == pdu)
	{
		return;
	}
	int iSended = 0;
	int iLeft = pdu->uiPDULen;
	int ret = -1;
	while (iLeft)
	{
		if (iLeft > PER_MAX_IO_BYTES)
		{
			ret = write(sockfd, (char *)pdu+iSended
						, PER_MAX_IO_BYTES);
		}
		else
		{
			ret = write(sockfd, (char *)pdu+iSended
					    , iLeft);
		}
		if (-1 == ret)
		{
			perror("send pdu write");
			break;
		}
		iSended += ret;
		iLeft -= ret;
	}
}
PDU *recvPDU(int sockfd)
{
	uint uiPDULen = 0;
	int ret = -1;
	ret = read(sockfd, &uiPDULen, sizeof(uint));
	if (0 == ret || -1 == ret)
	{
		return NULL;
	}

	uint uiMsgLen = uiPDULen-(sizeof(PDU)-4*sizeof(char));
	PDU *pdu = makePDU(uiMsgLen);

	int iRecved = sizeof(uint);
	int iLeft = uiPDULen-sizeof(uint);
	while (iLeft)
	{
		if (PER_MAX_IO_BYTES < iLeft)
		{
			ret = read(sockfd, (char*)pdu+iRecved
					   , PER_MAX_IO_BYTES);
		}
		else
		{
			ret = read(sockfd, (char*)pdu+iRecved
					   , iLeft);	
		}
		if (-1 == ret || 0 == ret)
		{
			break;
		}
		iRecved += ret;
		iLeft -= ret;
	}
	return pdu;
}











