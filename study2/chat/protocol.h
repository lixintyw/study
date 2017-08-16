#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "public.h"

enum ENUM_MSG_TYPE
{
	ENUM_MSG_TYPE_MIN = 0,
	ENUM_MSG_TYPE_REGIST_REQUEST,       //注册请求
	ENUM_MSG_TYPE_REGIST_RESPOND,       //注册回复
	ENUM_MSG_TYPE_LOGIN_REQUEST,        //登录请求
	ENUM_MSG_TYPE_LOGIN_RESPOND,        //登录回复
	ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST, //私聊请求
	ENUM_MSG_TYPE_PRIVATE_CHAT_RESPOND, //私聊回复
	ENUM_MSG_TYPE_GROUP_CHAT_REQUEST,   //群聊请求
	ENUM_MSG_TYPE_GROUP_CHAT_RESPOND,   //群聊回复
	ENUM_MSG_TYPE_EXIT_REQUEST,         //退出请求
	ENUM_MSG_TYPE_EXIT_RESPOND,         //退出回复
	ENUM_MSG_TYPE_MAX = 0x00ffffff
};

#define LOGIN_OK "ok"
#define LOGIN_FAILED "failed"

typedef struct PDU  //协议数据单元
{
	uint uiPDULen;        //消息的总的大小
	uint uiMsgType;       //消息的类型
	uint uiFrom;          //消息发送者的id
	uint uiTo;            //消息接收者的id
	uint uiMsgLen;        //实际消息的大小
	char caMsg[4];        //实际消息
}PDU;

PDU *makePDU(uint uiMsgLen);
void sendPDU(int sockfd, PDU *pdu);
PDU *recvPDU(int sockfd);

#endif











