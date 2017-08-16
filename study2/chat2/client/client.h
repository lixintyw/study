#ifndef CLIENT_H
#define CLIENT_H

#include "public.h"

int make_socket();
void connect_to_server(int sockfd);
int login_or_regist_face();
void login_or_regist(int sockfd);
void chat(int sockfd);
void exit_programs(int sockfd);
void look_file(int sockfd);
#endif






