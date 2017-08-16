#ifndef SERVER_H
#define SERVER_H

#include "public.h"

void set_base_id();
int make_socket();
void make_bind(int sockfd);
void make_listen(int sockfd);
void accept_client(int sockfd);

#endif
