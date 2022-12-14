#include <stdio.h>
#include <stdlib.h>
#include "clientTCP.c"
#include "URLparser.c"

#include "getip.c"

int main(int argc, char *argv[]){
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <URL to deconstruct>\nURL should be as follows: ftp://[<user>:<password>@]<host>/<url-path>\n", argv[0]);
        exit(-1);
    }

    char path[MAX_URL_SIZE];
    char host[MAX_URL_SIZE];
    char user[MAX_URL_SIZE];
    char password[MAX_URL_SIZE];
    char IPaddress[MAX_URL_SIZE];

    struct URL url;

    if(parseURL(argc,argv, &url)!=0){
        printf("Error occurred in fuction getDetails (main.c -- line 26)\n");
        exit(-1);
    }
    printf("\n");
    // if(getIP(host, IPaddress)!=0){
    //     printf("Error occurred in fuction getIP (main.c -- line 31)\n");
    //     exit(-1);
    // }
}