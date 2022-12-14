#pragma once

#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>

#define SERVER_PORT 6000
#define SERVER_ADDR "192.168.28.96"

int newSocket(char *ip, int port, int *sockfd);

int readReply(FILE* socket);

int sendCommand(int sockfd,char* cmd);

int readResponsePassive(FILE *socket, char (*ip)[], int *port);

int writeToFile(char *fileN, int socket);