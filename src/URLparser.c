#include "URLparser.h"

#define MAX_URL_SIZE 256

int parseURL(int argc, char *argv[], URL *url) {

    if (strncmp(argv[2], "ftp://", 6) != 0) {
        fprintf(stderr, "Error: not using FTP.\n\n");
        exit(-1);
    }

    strcpy(url->user, "\0");
    strcpy(url->password, "\0");

    // Parse the first argument to get the host and path
    sscanf(argv[2], "ftp://%[^/]/%s", url->host, url->path);

    // Parse the host string to get the user and password
    sscanf(url->host, "%[^:]:%[^@]@%[^/]", url->user, url->password, url->host);

    // If password is empty, use default values for user and password
    if(strlen(url->password)==0) {
        strcpy(url->user, "anonymous");
        strcpy(url->password, "apple123");
    }

    printf("\nUser: %s\nPwd: %s\nHost: %s\nPath: %s\n\n", url->user, url->password, url->host, url->path);

    if(getIP(url->host, url) != 0){
        printf("Error getting host name\n");
        return 1;
    }

    return 0;
}


int getIP(char *host, URL *url) {
    struct hostent *h;

    if ((h = gethostbyname(host)) == NULL){
        herror("gethostbyname()");
        return 1;
    }

    printf("IP Address : %s\n", inet_ntoa(*((struct in_addr *) h->h_addr)));

    strcpy(url->ip,inet_ntoa(*((struct in_addr *) h->h_addr)));

    return 0;
}
