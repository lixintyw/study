#ifndef CLIENT_H
#define CLIENT_H

#include "2public.c"

#include "2server.h"
#include "2list.h"
#include "2protocol.h"
#include "2file.h"
int make_socket();
void connect_to_server(int sockfd);
int login_or_regist_face();
void login_or_regist(int sockfd);
//void chat(int sockfd);
void handle_look_file(PDU *pdu);
//static void look_file(sockfd);
//static void download_file(sockfd);
//static void upload_file(sockfd);
//static void delete_file(sockfd);
//static void change_filename(sockfd);
int make_socket();
void file(int sockfd);
void exit_programs(int sockfd);

#endif
