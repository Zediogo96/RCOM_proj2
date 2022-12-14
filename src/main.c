//main function for a command line command of type download ftp://ftp.up.pt/pub/...

#include <stdio.h>
#include <stdlib.h>
#include "clientTCP.c"
#include "getip.c"
#include "URLparser.c"


int main (int argc, char *argv[]) {

    //Check if usage is correct and display if not

    if (argc != 2) {
        fprintf(stderr, "Usage: download <URL from which to download file \n URL format according to RFC1738: ftp://[<user>:<password@]<host>/<url-path> \n");
        exit(-1);
    }

    char host[256];  //check this, recommended max?
    char path[256];
    char ipaddr[15];  //size of an ip in chars = 15
    char user[256];
    char passwd [256];

    //parse URL to get details

    if (parseURL(argc, argv, host, path, user, passwd)) {
        exit(0);
        printf("Error occured while parsing URL\n");
        exit(-1);
    }

    //use getIP functiom (provided)

    if (getIP(host, ipaddr)) {
        printf("Error occured while getting IP address\n");
        exit(-1);
    }

    //open connection and use TCP with the provided data to get the file

    //TODO

}