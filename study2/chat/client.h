#ifndef CLIENT_H
#define CLIENT_H

#include "public.h"

int makeSocket();
void connectToServer(int sockfd);
int loginOrRegistFace();
void loginOrRegist(int sockfd);
void chat(int sockfd);
void exitPrograms(int sockfd);

#endif






