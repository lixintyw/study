#ifndef SERVER_H
#define SERVER_H

#include "2server.h"
#include "2list.h"
#include "2protocol.h"
#include "2file.h"
#include "public.h"

void set_base_id();
int make_socket();
void make_bind(int sockfd);
void make_listen(int sockfd);
void accept_client(int sockfd);
//static void handle_exit_request(int sockfd,PDU *pdu);
//static void handle_regist_request(int sockfd,PDU *pdu);
//static void handle_login_request(int sockfd,PDU *pdu);
//static void handle_look_file_request(int sockfd,PDU *pdu);
//static void *handle_client(void *arg);

#endif
