#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "public.h"

enum ENUM_MSG_TYPE
{
	//定义枚举类型变量
		//第一个是0
		//后面依次是1,2，……

	ENUM_MSG_TYPE_MIN = 0,
	ENUM_MSG_TYPE_REGIST_REQUEST,       //注册请求
	ENUM_MSG_TYPE_REGIST_RESPOND,       //注册回复
	ENUM_MSG_TYPE_LOGIN_REQUEST,        //登录请求
	ENUM_MSG_TYPE_LOGIN_RESPOND,        //登录回复
//	ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST, //私聊请求
//	ENUM_MSG_TYPE_PRIVATE_CHAT_RESPOND, //私聊回复
//	ENUM_MSG_TYPE_GROUP_CHAT_REQUEST,   //群聊请求
//	ENUM_MSG_TYPE_GROUP_CHAT_RESPOND,   //群聊回复
	ENUM_MSG_TYPE_LOOK_FILE_REQUEST,
	ENUM_MSG_TYPE_LOOK_FILE_RESPOND,
	ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST,
	ENUM_MSG_TYPE_DOWNLOAD_FILE_RESPOND,
	ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST,
	ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND,
	ENUM_MSG_TYPE_DELETE_FILE_REQUEST,
	ENUM_MSG_TYPE_DELETE_FILE_RESPOND,
	ENUM_MSG_TYPE_CHANGE_FILENAME_REQUEST,
	ENUM_MSG_TYPE_CHANGE_FILENAME_RESPOND,
	ENUM_MSG_TYPE_EXIT_REQUEST,         //退出请求
	ENUM_MSG_TYPE_EXIT_RESPOND,         //退出回复
	ENUM_MSG_TYPE_MAX = 0x00ffffff
};

#define LOGIN_OK "ok"
#define LOGIN_FAILED "failed"

typedef struct PDU//协议数据单元
{
	uint ui_pdu_len;//消息的总的大小
	uint ui_msg_type;//消息的类型
	uint ui_from;//消息发送者的id
	uint ui_to;//消息接收者的id
	uint ui_msg_len;//实际消息的大小
	char ca_filename[64];
	uint file_size;
	char ca_msg[4];//实际消息
}PDU;

PDU *make_pdu(uint ui_msg_len);
void send_pdu(int sockfd,PDU *pdu);
PDU *recv_pdu(int sockfd);

#endif


