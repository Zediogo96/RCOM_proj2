#pragma once
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#include <string.h>

#define URL_MAX_SIZE 256

// URL structure
typedef struct URL{
    char user[URL_MAX_SIZE];
    char password[URL_MAX_SIZE];
    char host[URL_MAX_SIZE];
    char path[URL_MAX_SIZE];
    char filename[URL_MAX_SIZE];
    char ip[URL_MAX_SIZE];
    int port;
} URL;

int parseURL(int argc, char *argv[], URL *url);

int getIP(char *host, URL *urlStruct);

void getPortPlusIp(int *port, char *ip, FILE *socket);

